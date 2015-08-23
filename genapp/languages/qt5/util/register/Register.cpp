#include "Register.h"
#include "../lib/jsoncons/json.hpp"
#include <map>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

using jsoncons::json;
using jsoncons::output_format;
using std::string;

const string Register::THRIFT_SERVER_HOST = "127.0.0.1" ;
const string Register::DEFAULT_GATEWAY = "default.registry.gateway" ;


struct module {
    string id;
    string name;
    string moduleId;
    string interfaceId;
};
vector<module> genapp_modules;
map<string,module> genapp_mod;
Register* Register::register_ = NULL;
bool Register::instanceFlag = false;


Register::Register()
{
    init();
}
Register::~Register(){}

void Register::init()
{
    this->moduleDir="";
    this->moduleId="";
    this->localhostId="";
    
    string directivesHome = get_current_dir_name();
    this->modulesFile = directivesHome + "/etc/menu.json";
    this->directivesFile = directivesHome + "/etc/directives.json";
    
    //remove comments from json file
    QFile read_menu(QString::fromStdString(this->modulesFile));
    QFile write_menu(QString::fromStdString(directivesHome + "/etc/menu_new.json"));
    

    write_menu.open(QIODevice::WriteOnly | QIODevice::Text);
    read_menu.open(QIODevice::ReadOnly | QIODevice::Text);
    

    QTextStream out(&write_menu);
    QTextStream in(&read_menu);
        while(!in.atEnd()) {
            QString line = in.readLine();
            string str = line.toStdString();
            if (str.find("#") != string::npos) {
                str = str.substr(0, str.find("#"));
               
            }
             out << QString::fromStdString(str) << endl;
        }
  

    read_menu.close();
    write_menu.close();
    read_menu.remove();

    QFile read_directives(QString::fromStdString(this->directivesFile));
    QFile write_directives(QString::fromStdString(directivesHome + "/etc/directives_new.json"));
   
    write_directives.open(QIODevice::WriteOnly | QIODevice::Text);
    read_directives.open(QIODevice::ReadOnly | QIODevice::Text);
   
    QTextStream outD(&write_directives);
    QTextStream inD(&read_directives);
        while(!inD.atEnd()) {
            cout << "Inside while" << endl;
            QString line = inD.readLine();
            string str = line.toStdString();
            cout << str << endl;
            if (str.find("#") != string::npos) {
                str = str.substr(0, str.find("#"));
               
            }
             outD << QString::fromStdString(str) << endl;
        }

    read_directives.close();
    write_directives.close();
    read_directives.remove();

    //rename the newly created json file
    string dir_name = directivesHome + "/etc";
    QDir dir(QString::fromStdString(dir_name));
    dir.rename("menu_new.json", "menu.json");
    dir.rename("directives_new.json", "directives.json");

    directivesHome += "/../..";
    
    //directive copy
    json directives_json = json::parse_file(this->directivesFile);
    json executable_path = directives_json["docroot"];
    this->outputDir = executable_path["qt5"].as<std::string>();

    this->moduleDir = directivesHome + "/bin";
    this->appConfig = directivesHome + "/appconfig.json";
    json modules = json::parse_file(this->modulesFile);
    json module_menus = modules["menu"].as<json::array>();
    for(size_t i=0;i<module_menus.size();i++)
    {
        json menu_modules = module_menus[i]["modules"].as<json::array>();
        for(size_t j=0;j<menu_modules.size();j++)
        {
            module new_module;
            new_module.id = menu_modules[j]["id"].as<std::string>();
            new_module.name = menu_modules[j]["label"].as<std::string>();
            genapp_mod[new_module.name] = new_module;
            genapp_modules.push_back(new_module);
        }
    }
    
}

typedef struct {
        gchar *airavata_server, *app_catalog_server;
        gint airavata_port, app_catalog_port, airavata_timeout;
} Settings;

void Register::readConfigFile(char* cfgfile, string& airavata_server, int& airavata_port, int& airavata_timeout) {

        json config_json = json::parse_file(this->appConfig);
        json resources_json = config_json["resources"];
        json airavata_json = resources_json["airavata"];
        json properties_json = airavata_json["properties"];
    
        airavata_server = properties_json["server"].as<std::string>();
        airavata_port = properties_json["port"].as<int>();
        airavata_timeout = properties_json["timeout"].as<int>();

}

void Register::registerAll()
{  
    
        int airavata_port, airavata_timeout;
        string airavata_server="";
        char* cfgfile = "./airavata-client-properties.ini";
        readConfigFile(cfgfile, airavata_server, airavata_port, airavata_timeout);  
        cout << "server-" << airavata_server << endl;            
        boost::shared_ptr<TSocket> socket(new TSocket(airavata_server, airavata_port));
        socket->setSendTimeout(airavata_timeout);
        boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));    
        boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
        airavataClient = new AiravataClient(protocol);
        
        transport->open();
        registerGateway();
        registerLocalhost();
        registerGatewayProfile();
        registerApplicationModules();
        registerApplicationDeployments();
        registerApplicationInterfaces();
        transport->close();
}

void Register::registerGateway() 
{
    try
    {
        cout << "registerGateway" << endl;
        Gateway gateway;
        gateway.__set_gatewayName("PHP Reference Gateway");
        gateway.__set_gatewayId("php_reference_gateway");
        airavataClient->addGateway(this->gatewayId,gateway);
        cout << "Gateway registered, id: " << this->gatewayId << endl;
    }
    catch(TException e)
    {
        cout << e.what() << endl;
    }
}

void Register::registerLocalhost() 
{
    try
    {
        cout << "\n #### Registering Localhost Computational Resources" << endl;
        string hostname="localhost";
        string hostDesc="LocalHost";
        vector<string> ipAddresses;
        vector<string> hostAliases;

        ComputeResourceDescription host;
        host.__set_hostName(hostname);
        host.__set_resourceDescription(hostDesc);
        
        airavataClient->registerComputeResource(this->localhostId,host);
        cout << "localhostId:" << this->localhostId << endl;
        ResourceJobManager resourceJobManager;
        map<JobManagerCommand::type, std::string> commandmap;
        resourceJobManager.__set_resourceJobManagerType(ResourceJobManagerType::FORK);
        resourceJobManager.__set_pushMonitoringEndpoint("");
        resourceJobManager.__set_jobManagerBinPath("");
        resourceJobManager.__set_jobManagerCommands(commandmap);
    

        LOCALSubmission localSubmission;
        localSubmission.__set_resourceJobManager(resourceJobManager);

        string submission = "";
        
        airavataClient->addLocalSubmissionDetails(submission,this->localhostId,1,localSubmission);

        cout << "submission:" << submission << endl;
        cout << "Localhost Resource Id is " << this->localhostId << endl;     
    }
    catch(TException& e)
    {
        cout << e.what() << endl;
    }
}

void Register::registerGatewayProfile()
{
    try
    {
        DataMovementProtocol::type dataMovementProtocol;
        string scratchlocation = this->outputDir; 
        
        char* cLocation = new char[scratchlocation.length()+ 1];
        strcpy(cLocation,scratchlocation.c_str());

        struct stat info;
        int err = stat(cLocation, &info);
        if(err!=-1 && S_ISDIR(info.st_mode))
            scratchlocation = this->outputDir;
        else{
            cout << "Output directory- " << this->outputDir << " -doesn't exist..check \"docroot\" in directives.json" << endl;
            exit(1);
        }
        JobSubmissionProtocol::type jobSubmissionProtocol;
        string preferredBatchQueue;
        bool overridebyAiravata = false;
        string allocationProjectNumber = "Sample";
        string computeResourceId = this->localhostId;
        cout << "ComputeResourceId:" << computeResourceId << endl;
        ComputeResourcePreference localhostResourcePreference;
        localhostResourcePreference.__set_computeResourceId(computeResourceId);
        localhostResourcePreference.__set_allocationProjectNumber(allocationProjectNumber);
        localhostResourcePreference.__set_overridebyAiravata(overridebyAiravata); 
        localhostResourcePreference.__set_preferredBatchQueue(preferredBatchQueue);
        localhostResourcePreference.__set_preferredJobSubmissionProtocol(jobSubmissionProtocol);
        localhostResourcePreference.__set_preferredDataMovementProtocol(dataMovementProtocol);
        localhostResourcePreference.__set_scratchLocation(scratchlocation);

        GatewayResourceProfile gatewayResourceProfile;
        gatewayResourceProfile.__set_gatewayID(this->gatewayId);
        std::vector<ComputeResourcePreference> crpVector;
        crpVector.push_back(localhostResourcePreference);
        gatewayResourceProfile.__set_computeResourcePreferences(crpVector);
        string _registerGatewayResourceProfile="";
        airavataClient->registerGatewayResourceProfile(_registerGatewayResourceProfile,gatewayResourceProfile);
        cout << "gateway profile registered:" << _registerGatewayResourceProfile << endl;
        
    }
    catch(TException e)
    {
        cout << e.what() << endl;
    }
}

void Register::registerApplicationModules() 
{
    try
    {   
        for(std::vector<module>::iterator it = genapp_modules.begin(); it != genapp_modules.end(); it++) 
        {
            string moduleName = it->name;
            string appModuleVersion = "1.0";
            string appModuleDescription = moduleName+" application description";
            ApplicationModule appModule;
            appModule.__set_appModuleName(moduleName);
            appModule.__set_appModuleVersion(appModuleVersion);
            appModule.__set_appModuleDescription(appModuleDescription);
            airavataClient->registerApplicationModule(it->moduleId,this->gatewayId,appModule);

        }
    }
    catch(TException& e)
    {
        cout << e.what() << endl;
    }
}

void Register::registerApplicationDeployments()
{
    try
    {
        for(std::vector<module>::iterator it = genapp_modules.begin(); it != genapp_modules.end(); it++) 
        {
            cout << "#### Registering Genapp Modules on Localhost ####" << endl;
            string moduleName = it->name;
            string moduleId = it->moduleId;
            string moduleDeployId="";
            string computeResourceId = this->localhostId;
            string executablePath = moduleDir + "/" +it->id;
            ApplicationDeploymentDescription applicationDeploymentDescription;
            applicationDeploymentDescription.__set_appModuleId(moduleId);
            applicationDeploymentDescription.__set_computeHostId(computeResourceId);
            applicationDeploymentDescription.__set_executablePath(executablePath);
            applicationDeploymentDescription.__set_parallelism(ApplicationParallelismType::SERIAL);
            applicationDeploymentDescription.__set_appDeploymentDescription(moduleName);
            airavataClient->registerApplicationDeployment(moduleDeployId,this->gatewayId,applicationDeploymentDescription);
            cout << "Successfully registered " << moduleName << " application on localhost. Id= " << moduleDeployId << endl;
        }
    }
    catch(TException& e)
    {
        cout << e.what() << endl;
    }
}

void Register::registerApplicationInterfaces()
{   
    for(std::vector<module>::iterator it = genapp_modules.begin(); it != genapp_modules.end(); it++) 
    {
        string moduleName = it->name;
        string moduleId = it->moduleId;
        registerApplicationInterface(moduleName,moduleId);
    }
}



void Register::registerApplicationInterface(string moduleName,string moduleId)
{
    try
    {
        cout << "#### Registering " << moduleName << " Interface ####" << endl;

        vector<string> appModules;
        appModules.push_back(moduleId);

        InputDataObjectType input;
        string inputName = "Input_JSON";
        string inputValue = "{}";
        apache::airavata::model::appcatalog::appinterface::DataType::type type = apache::airavata::model::appcatalog::appinterface::DataType::STRING;
        string applicationArgument="";
        bool stdIn = false;
        string description = "JSON String";
        string metaData="";

        if(!inputName.empty())
            input.__set_name(inputName);
        if(!inputValue.empty())
            input.__set_value(inputValue);
        input.__set_type(type);
        if(!applicationArgument.empty())
            input.__set_applicationArgument(applicationArgument);
        input.__set_standardInput(stdIn);
        if(!description.empty())
            input.__set_userFriendlyDescription(description);
        if(!metaData.empty())
            input.__set_metaData(metaData);

        vector<InputDataObjectType> applicationInputs;
        applicationInputs.push_back(input);
        
        string outputName = "Output_JSON";
        string outputValue = "{}";
        
        OutputDataObjectType output;
        if(!outputName.empty())
            output.__set_name(outputName);
        if(!outputValue.empty())
            output.__set_value(outputValue);
        output.__set_type(type);

        std::vector<OutputDataObjectType> applicationOutputs;
        applicationOutputs.push_back(output);

        string ModuleInterfaceId = "";
        ApplicationInterfaceDescription applicationInterfaceDescription;
        applicationInterfaceDescription.__set_applicationName(moduleName);
        applicationInterfaceDescription.__set_applicationDescription(moduleName + " the inputs");
        applicationInterfaceDescription.__set_applicationModules(appModules);
        applicationInterfaceDescription.__set_applicationInputs(applicationInputs);
        applicationInterfaceDescription.__set_applicationOutputs(applicationOutputs);

        airavataClient->registerApplicationInterface(ModuleInterfaceId,this->gatewayId,applicationInterfaceDescription);
        genapp_mod[moduleName].interfaceId = ModuleInterfaceId;
        cout << moduleName << " Module Interface Id: " << genapp_mod[moduleName].interfaceId  << endl;
    }
    catch(TException& e)
    {
        cout << e.what() << endl;
    }
}

void Register::registerMain(Register* registerGenapp)
{
    try
    {
        //registerGenapp->init();
        registerGenapp->registerAll();
    }
    catch(AiravataClientException& e1)
    {
        std::cerr<<"Cannot connect to server-"<< e1.what() <<endl;
    }
    catch(TException& e2)
    {
        cerr << e2.what() << endl;
    }
}

string Register::getGatewayId()
{ 
    return this->gatewayId;
}

string Register::getInterfaceId(string moduleName)
{
    if(genapp_mod.find(moduleName)==genapp_mod.end())
        return "Error: Module not found";
    else
        return genapp_mod[moduleName].interfaceId;
}

string Register::getComputeResourceId()
{
    cout << "ComputeResourceId: " << this->localhostId << endl;
    return this->localhostId;
}

Register* Register::getInstance()
{
    if(!instanceFlag)
    {
        register_ = new Register();
        instanceFlag = true;
        return register_ ;
    }
    else
    {
        return register_;
    }
}



string gatewayId;

string createProject(char* owner, char* projectName)
{ 
    int airavata_port, airavata_timeout;
    string airavata_server;
    char* cfgfile;
    cfgfile = "./airavata-client-properties.ini";
    Register* register_= Register::getInstance();
    register_->readConfigFile(cfgfile, airavata_server, airavata_port, airavata_timeout);  
    boost::shared_ptr<TSocket> socket(new TSocket(airavata_server, airavata_port));
    socket->setSendTimeout(airavata_timeout);
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));    
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    AiravataClient airavataClient(protocol);
    transport->open();
    apache::airavata::model::workspace::Project project;                
    project.owner=owner;
    project.name=projectName;
    string _return;
    gatewayId = register_->getGatewayId();
    cout << "Gateway Id:" << gatewayId << endl;
    airavataClient.createProject(_return,gatewayId,project);                
    transport->close();
    return _return;
}

string createExperiment(char* usrName, char* expName, char* projId, char* execId, char* inp)
{
    int airavata_port, airavata_timeout;
    string airavata_server;
    char* cfgfile;
    cfgfile = "./airavata-client-properties.ini";
    Register* register_= Register::getInstance();   
    register_->readConfigFile(cfgfile, airavata_server, airavata_port, airavata_timeout);  
    boost::shared_ptr<TSocket> socket(new TSocket(airavata_server, airavata_port));
    socket->setSendTimeout(airavata_timeout);
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));    
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    AiravataClient airavataClient(protocol);
    transport->open();
    ComputationalResourceScheduling cmRST;
    cmRST.__set_resourceHostId(register_->getComputeResourceId());
    cmRST.__set_computationalProjectAccount(usrName);
    cmRST.__set_totalCPUCount(1);
    cmRST.__set_nodeCount(1);
    cmRST.__set_numberOfThreads(1);
    cmRST.__set_queueName("normal");
    cmRST.__set_wallTimeLimit(30);
    cmRST.__set_jobStartTime(0);
    cmRST.__set_totalPhysicalMemory(1);


    UserConfigurationData userConfigurationData;
    userConfigurationData.__set_airavataAutoSchedule(false);
    userConfigurationData.__set_overrideManualScheduledParams(false);
    userConfigurationData.__set_computationalResourceScheduling(cmRST);


    
    char* appId = execId;        

     
    InputDataObjectType input;
    input.__set_name("input");
    input.__set_value(inp);
    input.__set_type(DataType::STRING);
    std::vector<InputDataObjectType> exInputs;
    exInputs.push_back(input);              
    OutputDataObjectType output;
    output.__set_name("output");
    output.__set_value("");
    output.__set_type(DataType::STDOUT);
    std::vector<OutputDataObjectType> exOutputs;
    exOutputs.push_back(output);


    char* user = usrName;
    char* exp_name = expName;
    char* proj = projId;

    Experiment experiment;
    experiment.__set_projectID(proj);
    experiment.__set_userName(user);
    experiment.__set_name(exp_name);
    experiment.__set_applicationId(appId);
    experiment.__set_userConfigurationData(userConfigurationData);
    experiment.__set_experimentInputs(exInputs);
    experiment.__set_experimentOutputs(exOutputs);
              
    string _return = "";
    
    airavataClient.createExperiment(_return, gatewayId, experiment);
    transport->close();
    return _return;
}

void launchExperiment(char* expId)
{
    try {
            int airavata_port, airavata_timeout;
            string airavata_server;
            char* cfgfile;
            cfgfile = "./airavata-client-properties.ini";
            Register* register_= Register::getInstance();   
            register_->readConfigFile(cfgfile, airavata_server, airavata_port, airavata_timeout);  
            boost::shared_ptr<TSocket> socket(new TSocket(airavata_server, airavata_port));
            socket->setSendTimeout(airavata_timeout);
            boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));    
            boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
            AiravataClient airavataClient(protocol);
            transport->open();              
            string tokenId = "-0bbb-403b-a88a-42b6dbe198e9";
            airavataClient.launchExperiment(expId, "airavataToken");
            qDebug() << "launched client experiment";
            transport->close();             
        } catch (ExperimentNotFoundException e) {
            cout << "Error occured while launching the experiment..." << e.what() << endl;
            throw new ExperimentNotFoundException(e);
        } catch (AiravataSystemException e) {
            cout << "Error occured while launching the experiment..." << e.what() << endl;
            throw new AiravataSystemException(e);
        } catch (InvalidRequestException e) {
            cout << "Error occured while launching the experiment..." << e.what() << endl;
            throw new InvalidRequestException(e);
        } catch (AiravataClientException e) {
            cout << "Error occured while launching the experiment..." << e.what() << endl;
            throw new AiravataClientException(e);
        } catch (TException e) {
            cout << "Error occured while launching the experiment..." << e.what() << endl;
            throw new TException(e);
        }
    // airavataclient.launchExperiment(expId, "airavataToken");
    // transport->close();             
}

int getExperimentStatus(char* expId)
{
    int airavata_port, airavata_timeout;
    string airavata_server;
    char* cfgfile;
    cfgfile = "./airavata-client-properties.ini";
    Register* register_= Register::getInstance();   
    register_->readConfigFile(cfgfile, airavata_server, airavata_port, airavata_timeout);  
    boost::shared_ptr<TSocket> socket(new TSocket(airavata_server, airavata_port));
    socket->setSendTimeout(airavata_timeout);
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));    
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    AiravataClient airavataClient(protocol);
    transport->open();          
    ExperimentStatus _return;       
    airavataClient.getExperimentStatus(_return, expId);
    transport->close();
    return _return.experimentState;
                
}

string getExperimentOutput(char* expId)
{
    int airavata_port, airavata_timeout;
    string airavata_server;
    char* cfgfile;
    cfgfile = "./airavata-client-properties.ini";
    Register* register_= Register::getInstance();   
    register_->readConfigFile(cfgfile, airavata_server, airavata_port, airavata_timeout);  
    boost::shared_ptr<TSocket> socket(new TSocket(airavata_server, airavata_port));
    socket->setSendTimeout(airavata_timeout);
    boost::shared_ptr<TTransport> transport(new TBufferedTransport(socket));    
    boost::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));
    AiravataClient airavataClient(protocol);
    transport->open();          
    std::vector<OutputDataObjectType> _return;
    string texpId(expId);
    airavataClient.getExperimentOutputs(_return, texpId);
    transport->close();
    return _return[0].value;
                
}