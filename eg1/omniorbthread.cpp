#include "omniorbthread.h"

#include "echo.h"

#ifdef HAVE_STD
#  include <iostream>
   using namespace std;
#else
#  include <iostream.h>
#endif

// This is the object implementation.

class Echo_i : public POA_Echo
{
public:
  inline Echo_i() {}
  virtual ~Echo_i() {}
  virtual char* echoString(const char* mesg);
};


char* Echo_i::echoString(const char* mesg)
{
  return CORBA::string_dup(mesg);
}


//////////////////////////////////////////////////////////////////////

// This function acts as a client to the object.

static void hello(Echo_ptr e)
{
  if( CORBA::is_nil(e) ) {
    cerr << "hello: The object reference is nil!\n" << endl;
    return;
  }

  CORBA::String_var src = (const char*) "Hello!";
  // String literals are (char*) rather than (const char*) on some
  // old compilers.  Thus it is essential to cast to (const char*)
  // here to ensure that the string is copied, so that the
  // CORBA::String_var does not attempt to 'delete' the string
  // literal.

  CORBA::String_var dest = e->echoString(src);

  cout << "I said, \"" << (char*)src << "\"." << endl
       << "The Echo object replied, \"" << (char*)dest <<"\"." << endl;
}

//////////////////////////////////////////////////////////////////////

OmniORBThread::OmniORBThread(int argc, char **argv, QObject *parent)
    : QThread(parent), _argc(argc), _argv(argv)
{
}

OmniORBThread::~OmniORBThread()
{
    cout << "OmniORBThread is over!";
}

void OmniORBThread::run()
{
  try {
    // Initialise the ORB.
    CORBA::ORB_var orb = CORBA::ORB_init(_argc, _argv);

    // Obtain a reference to the root POA.
    CORBA::Object_var obj = orb->resolve_initial_references("RootPOA");
    PortableServer::POA_var poa = PortableServer::POA::_narrow(obj);

    // We allocate the object on the heap.  Since this is a reference
    // counted object, it will be deleted by the POA when it is no
    // longer needed.
    Echo_i* myecho = new Echo_i();

    // Activate the object.  This tells the POA that this object is
    // ready to accept requests.
    PortableServer::ObjectId_var myechoid = poa->activate_object(myecho);

    // Obtain a reference to the object.
    Echo_var myechoref = myecho->_this();

    // Decrement the reference count of the object implementation, so
    // that it will be properly cleaned up when the POA has determined
    // that it is no longer needed.
    myecho->_remove_ref();

    // Obtain a POAManager, and tell the POA to start accepting
    // requests on its objects.
    PortableServer::POAManager_var pman = poa->the_POAManager();
    pman->activate();

    // Do the client-side call.
    hello(myechoref);

    // Clean up all the resources.
    orb->destroy();
  }
  catch(CORBA::SystemException& ex) {
    cerr << "Caught CORBA::" << ex._name() << endl;
  }
  catch(CORBA::Exception& ex) {
    cerr << "Caught CORBA::Exception: " << ex._name() << endl;
  }
  catch(omniORB::fatalException& fe) {
    cerr << "Caught omniORB::fatalException:" << endl;
    cerr << "  file: " << fe.file() << endl;
    cerr << "  line: " << fe.line() << endl;
    cerr << "  mesg: " << fe.errmsg() << endl;
  }

  //emit finished();
}