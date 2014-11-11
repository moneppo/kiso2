#ifndef KisoApp_Header
#define KisoApp_Header

#include <jni.h>
#include "yaml-cpp/yaml.h"
#include <string>
#include "uv.h"

#define FPS 60

class KisoApp {
public:
  KisoApp(std::string uri, std::string storageLocation);
	virtual ~KisoApp();
	
	uv_loop_t* loop() { return &m_loop; }
	std::string storageLocation() { return m_storageLocation; }
	std::string appKey() { return m_appKey; }
	YAML::Node* presentation() { return &m_presentation; }
	YAML::Node* structure() { return &m_structure; }
	JNIEnv* vm() { return m_env; }
	
	void startVM();
	
protected:

	void createVM();
	static void VMCallback(void* arg);
  
  YAML::Node m_structure;
  YAML::Node m_presentation;
	YAML::Node m_manifest;
	uv_loop_t m_loop;
	std::string m_storageLocation;
	std::string m_appKey;
	JNIEnv* m_env;
};

#endif