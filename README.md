**Update**
-------------
For using messaging services in qt, refer to the [develop](https://github.com/priyanshu-sekhar/GenApp/tree/develop) branch. <br/>

##GENAPP AIRAVATA INTEGRATION
==========================

Dependencies
---------------------
* glib <br/>
* thrift <br/>
* boost (Recommended for developers) <br/>
* Airavata (to run it on server) - [Install Airavata](https://docs.google.com/document/d/1xmGorQjlllJB9nxlCg0zHJu7UKibuzjYDI_zowm5Yng/edit) <br/>

Building from scratch
---------------------
Follow the steps below to build, configure and run genapp interfaces from scratch. <br/>

1. Set up developement environment as listed on [GenApp Wiki](http://gw105.iu.xsede.org:8000/genapp/wiki/setupdev) <br/>
2. Set GENAPP environment vairable to the location of genapp folder and add $GENAPP/bin to your PATH <br/>
3. Change to *psptest* <br/>
4. Execute __genapp.pl__ <br/>

Generated Code will be present in psptest/output <br/>

Steps to Install Qt5(for linux/X11)
-------------------------------------
1. Download the latest Qt5 version from http://www.qt.io/download/ and run the application (Don't launch the Qt5 creator) <br/>
2. Download the latest version of Qwt (6.1+) from http://qwt.sourceforge.net/qwtinstall.html and follow the steps for installation <br/>
3. Open terminal(from which you wish to run Genapp-Qt5) <br/>
4. Execute the following command: <br/>
   ```
   PATH=/path/to/Qt5/gcc_64/bin:$PATH && export PATH 
   (Assuming qmake lies inside /path/to/Qt5/gcc_64/bin, or specify path to qmake)
   ```
   ######check
   "qmake -v" should display the installed version of Qt5 <br/>

5. Execute: qmake -set QMAKEFEATURES /usr/local/qwt-6.1.2/features/  <br/>
   (Replace qwt-6.1.2 with your installed version and change it's path if installed in a different directory) <br/>

Tip: You can make the PATH settings permanent by editing in the ".bashrc" or equivalent file. <br/>
You are now ready to proceed with running the Qt5 application :) <br/>
For more info, visit the official [qt5](http://doc.qt.io/qt-5/linux-deployment.html) documentation <br/>
-------------------------------------

C++/Qt4
-----------------
1. Change to "psptest/output/qt4/psptest" <br/>
2. Execute "qmake-qt4 -project" <br/>
3. Edit "psptest.pro" to add the following lines: <br/>
   ```
   INCLUDEPATH += /usr/include/qwt-qt4 ../lib/ <br/>
   LIBS += `pkg-config --libs glib-2.0` -L/usr/local/lib -lthrift -lqwt-qt4 
   QMAKE_CXXFLAGS += -w -Wall -std=c++11 -Wno-write-strings -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H  `pkg-config --cflags glib-2.0`
   ```
4. Execute *qmake-qt4* <br/>
5. Execute *make* <br/>
6. Change to "genapp-output/psptest/output/qt4" directory <br/>
7. Run executable ./psptest/psptest <br/>

C++/Qt5
---------------
1. Complete the steps specified in "Steps to Install Qt5(for linux/X11)" <br/>
2. Go to "psptest/output/qt5/psptest" <br/>
3. Perform "make clean" if built previously, else skip this. <br/>
4. Execute "qmake -project" <br/>
5. Edit "psptest.pro" to add the following lines: <br/>
   ```
   CONFIG += qwt
   INCLUDEPATH += ../lib/
   LIBS += `pkg-config --libs glib-2.0` -lthrift 
   QMAKE_CXXFLAGS += -w -Wall -std=c++11 -Wno-write-strings -DHAVE_INTTYPES_H -DHAVE_NETINET_IN_H  `pkg-config --cflags glib-2.0` 
   ```
6. Execute "qmake -config release" to statically link the Qt libraries <br/>
7. Execute "make" to build and create the executable. <br/>
8. Execute "cd .." to goto "psptest/output/qt5" <br/>
9. Run executable ./psptest/psptest <br/>

