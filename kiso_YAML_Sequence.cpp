#include "kiso_YAML_Sequence.h"
#include "yaml-cpp/include/yaml-cpp/yaml.h"
#include <string>

using namespace std;

void setNode( JNIEnv *env, jobject je, YAML::Node *ps )
{
  jclass clas = env->GetObjectClass( je );
  jfieldID fid = env->GetFieldID( clas, "eptr", "I" );
  env->SetIntField( je, fid, *(int *) ps );
}

YAML::Node *getNode( JNIEnv *env, jobject je )
{
  jclass clas = env->GetObjectClass( je );
  jfieldID fid = env->GetFieldID( clas, "eptr", "I" );

  YAML::Node *ps = (YAML::Node*)(env->GetIntField( je, fid ));

  return ps;
}


/*
 * Class:     kiso_YAML_Sequence
 * Method:    initialize
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_kiso_YAML_Sequence_initialize
  (JNIEnv *env, jobject je)
{
  setNode( env, je, new YAML::Node() );
}

/*
 * Class:     kiso_YAML_Sequence
 * Method:    getString
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_kiso_YAML_Sequence_getScalar
  (JNIEnv *env, jobject je, jint index)
{
  YAML::Node* node = getNode(env, je);
  //try {
    string result = (*node)[index].as<string>();
    return env->NewStringUTF( result.c_str());
  //}
}

/*
 * Class:     kiso_YAML_Sequence
 * Method:    getSequence
 * Signature: (I)Lkiso/YAML/Sequence;
 */
JNIEXPORT jobject JNICALL Java_kiso_YAML_Sequence_getSequence
  (JNIEnv *env, jobject je, jint index)
{
  jclass cls = env->FindClass("kiso/YAML/Sequence");
  jmethodID constructor = env->GetMethodID(cls, "<init>", "void(V)");
  YAML::Node* node = getNode(env, je);
  YAML::Node seq = (*node)[index];
  
  jobject result = env->NewObject(cls, constructor);
  setNode(env, result, &seq);
  
  return result;
}

/*
 * Class:     kiso_YAML_Sequence
 * Method:    getMap
 * Signature: (I)Lkiso/YAML/Map;
 */
JNIEXPORT jobject JNICALL Java_kiso_YAML_Sequence_getMap
  (JNIEnv *env, jobject je, jint index)
{
  jclass cls = env->FindClass("kiso/YAML/Map");
  jmethodID constructor = env->GetMethodID(cls, "<init>", "void(V)");
  YAML::Node* node = getNode(env, je);
  YAML::Node map = (*node)[index];
  
  jobject result = env->NewObject(cls, constructor);
  setNode(env, result, &map);
  
  return result;
}

/*
 * Class:     kiso_YAML_Sequence
 * Method:    type
 * Signature: (I)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_kiso_YAML_Sequence_type
  (JNIEnv *env, jobject je, jint index)
{
  YAML::Node* node = getNode(env, je);
  switch((*node)[index].Type()) {
    case YAML::NodeType::Sequence:
      return env->NewStringUTF( "sequence" );
    case YAML::NodeType::Scalar:
      return env->NewStringUTF( "scalar" );
    case YAML::NodeType::Null:
      return env->NewStringUTF( "null" );
		    case YAML::NodeType::Undefined:
      return env->NewStringUTF( "undefined" ); 
    case YAML::NodeType::Map:
      return env->NewStringUTF( "map" );  
  }
}

/*
 * Class:     kiso_YAML_Sequence
 * Method:    length
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_kiso_YAML_Sequence_length
  (JNIEnv *env, jobject je)
{
  YAML::Node* node = getNode(env, je);
  return node->size();
}

/*
 * Class:     kiso_YAML_Sequence
 * Method:    remove
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_kiso_YAML_Sequence_remove
  (JNIEnv *env, jobject je, jint index)
{
   YAML::Node* node = getNode(env, je);
   node->remove<int>(index);
}

/*
 * Class:     kiso_YAML_Sequence
 * Method:    setString
 * Signature: (ILjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_kiso_YAML_Sequence_setScalar
  (JNIEnv *env, jobject je, jint index, jstring scalar)
{
  YAML::Node* node = getNode(env, je);
  jboolean b;
  (*node)[index] = env->GetStringUTFChars( scalar, &b );
}

/*
 * Class:     kiso_YAML_Sequence
 * Method:    setSequence
 * Signature: (ILkiso/YAML/Sequence;)V
 */
JNIEXPORT void JNICALL Java_kiso_YAML_Sequence_setSequence
  (JNIEnv *env, jobject je, jint index, jobject jseq)
{
  YAML::Node *seq = getNode(env, jseq);
  YAML::Node *node = getNode(env, je);
  
  (*node)[index] = *seq;
}

/*
 * Class:     kiso_YAML_Sequence
 * Method:    setMap
 * Signature: (ILkiso/YAML/Map;)V
 */
JNIEXPORT void JNICALL Java_kiso_YAML_Sequence_setMap
  (JNIEnv *env, jobject je, jint index, jobject jmap)
{
  YAML::Node *map = getNode(env, jmap);
  YAML::Node *node = getNode(env, je);
  
  (*node)[index] = *map;
}
