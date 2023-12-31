/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class com_hesong_ipsc_busnetcli_Client */

#ifndef _Included_com_hesong_ipsc_busnetcli_Client
#define _Included_com_hesong_ipsc_busnetcli_Client
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     com_hesong_ipsc_busnetcli_Client
 * Method:    initiateLibrary
 * Signature: (B)I
 */
JNIEXPORT jint JNICALL Java_com_hesong_ipsc_busnetcli_Client_initiateLibrary
  (JNIEnv *, jclass, jbyte);

/*
 * Class:     com_hesong_ipsc_busnetcli_Client
 * Method:    releaseLibrary
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_hesong_ipsc_busnetcli_Client_releaseLibrary
  (JNIEnv *, jclass);

/*
 * Class:     com_hesong_ipsc_busnetcli_Client
 * Method:    createConnect
 * Signature: (BILjava/lang/String;SLjava/lang/String;SLjava/lang/String;Ljava/lang/String;Ljava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_hesong_ipsc_busnetcli_Client_createConnect
  (JNIEnv *, jclass, jbyte, jint, jstring, jshort, jstring, jshort, jstring, jstring, jstring);

/*
 * Class:     com_hesong_ipsc_busnetcli_Client
 * Method:    launchFlow
 * Signature: (BIILjava/lang/String;Ljava/lang/String;IILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_hesong_ipsc_busnetcli_Client_launchFlow
  (JNIEnv *, jclass, jbyte, jint, jint, jstring, jstring, jint, jint, jstring);

/*
 * Class:     com_hesong_ipsc_busnetcli_Client
 * Method:    sendNotification
 * Signature: (BIILjava/lang/String;Ljava/lang/String;IILjava/lang/String;)I
 */
JNIEXPORT jint JNICALL Java_com_hesong_ipsc_busnetcli_Client_sendNotification
  (JNIEnv *, jclass, jbyte, jint, jint, jstring, jstring, jint, jint, jstring);

/*
 * Class:     com_hesong_ipsc_busnetcli_Client
 * Method:    sendData
 * Signature: (BBBIII[B)I
 */
JNIEXPORT jint JNICALL Java_com_hesong_ipsc_busnetcli_Client_sendData
  (JNIEnv *, jclass, jbyte, jbyte, jbyte, jint, jint, jint, jbyteArray);

#ifdef __cplusplus
}
#endif
#endif
