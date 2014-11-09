#include "KisoApp.h"

using namespace std;

KisoApp::KisoApp( string uri, string storageLocation ) :
	m_storageLocation(storageLocation)
{
  // TODO: Network connectivity check to skip downloading manifest
  
  // 1. Look at the manifest file
  // 2. Check for any updates from the current version
  // 3. Download new resources if needed
	m_manifest = YAML::Load("");
		
	m_appKey = "";
	
  // 4. Parse YAML, build layout
	YAML::Node root = YAML::Node("");
	m_structure = root["structure"];
	m_presentation = root["presentation"];
	
	//uv_loop_init( &m_loop );
		
	// m_renderer = new KisoRenderer(m_loop);
}
  
KisoApp::~KisoApp() { 
	//uv_loop_close( &m_loop );
	// delete m_renderer;
}

void KisoApp::createVM() {
	JavaVM* jvm;
	JavaVMInitArgs args;
	JavaVMOption options[1];
	
	args.version = JNI_VERSION_1_6;
	args.nOptions = 1;
	char optionString[] = "-Djava.class.path=.";
	options[0].optionString = optionString;
	args.options = options;
	args.ignoreUnrecognized = JNI_FALSE;

	JNI_CreateJavaVM(&jvm, (void **)&m_env, &args);
}

void KisoApp::startVM() 
{
	createVM();
	
	uv_thread_t vm_id;
	
	// Need to link in services for http requests, file i/o, etc.
	// These can use the async libuv mechanism
	// Again, figure out thread safety.

	uv_thread_create(&vm_id, VMCallback, (void*) this);
}

void KisoApp::VMCallback(void* arg)
{
	KisoApp* self = (KisoApp *) arg;
	string classPath = self->m_manifest["classPath"].as<string>();
	jclass cls = self->m_env->FindClass( classPath.c_str() );
	jmethodID mainMethod = self->m_env->GetStaticMethodID( cls, "main", "([Ljava/lang/String;)V");
	self->m_env->CallStaticVoidMethod(cls, mainMethod);
}