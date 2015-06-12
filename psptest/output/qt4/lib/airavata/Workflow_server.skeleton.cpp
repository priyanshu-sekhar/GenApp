/**
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "Workflow.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>

using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::apache::airavata::api;

class WorkflowHandler : virtual public WorkflowIf {
 public:
  WorkflowHandler() {
    // Your initialization goes here
  }

  void getAllWorkflows(std::vector<std::string> & _return) {
    // Your implementation goes here
    printf("getAllWorkflows\n");
  }

  void getWorkflow( ::Workflow& _return, const std::string& workflowTemplateId) {
    // Your implementation goes here
    printf("getWorkflow\n");
  }

  void deleteWorkflow(const std::string& workflowTemplateId) {
    // Your implementation goes here
    printf("deleteWorkflow\n");
  }

  void registerWorkflow(std::string& _return, const  ::Workflow& workflow) {
    // Your implementation goes here
    printf("registerWorkflow\n");
  }

  void updateWorkflow(const std::string& workflowTemplateId, const  ::Workflow& workflow) {
    // Your implementation goes here
    printf("updateWorkflow\n");
  }

  void getWorkflowTemplateId(std::string& _return, const std::string& workflowName) {
    // Your implementation goes here
    printf("getWorkflowTemplateId\n");
  }

  bool isWorkflowExistWithName(const std::string& workflowName) {
    // Your implementation goes here
    printf("isWorkflowExistWithName\n");
  }

};

int main(int argc, char **argv) {
  int port = 9090;
  shared_ptr<WorkflowHandler> handler(new WorkflowHandler());
  shared_ptr<TProcessor> processor(new WorkflowProcessor(handler));
  shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
  shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
  shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

  TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
  server.serve();
  return 0;
}

