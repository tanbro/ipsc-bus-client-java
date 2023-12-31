/*
 * Client.c
 *
 *  Created on: 2016-7-11
 *      Author: liuxy
 */

#include "com_hesong_ipsc_busnetcli_Client.h"

#include <stdbool.h>

#include <stdexcept>

#include <smartbus_netcli_interface.h>
#include "callbacks.h"
#include "globvars.h"

using namespace std;

jint JNICALL Java_com_hesong_ipsc_busnetcli_Client_initiateLibrary(
    JNIEnv* env, jclass cls, jbyte unit_id) {
  env->GetJavaVM(&jvm);
  // Get Client Class
  cls_client = cls;
  // Init
  // int result = SmartBusNetCli_InitEx((unsigned char) unit_id,
  // "OpenSignalProcess=1");
  int result = SmartBusNetCli_Init((unsigned char)unit_id);
  if (result != SMARTBUS_ERR_OK) {
    return (jint)result;
  }
  // Set callbacks
  meth_client_globalconenct = env->GetStaticMethodID(
      cls, "callbackGlobalConnect", "(BBBBLjava/lang/String;)V");
  meth_client_connect =
      env->GetStaticMethodID(cls, "callbackConnect", "(BII)V");
  meth_client_disconnect =
      env->GetStaticMethodID(cls, "callbackDisconnect", "(B)V");
  meth_client_recvdata =
      env->GetStaticMethodID(cls, "callbackData", "(BBBBBBBB[B)V");
  meth_client_log = env->GetStaticMethodID(cls, "callbackLog", "([BZ)V");
  SmartBusNetCli_SetCallBackFn(connection, recvdata, disconnect, NULL,
                               global_connect, NULL);
  SmartBusNetCli_SetTraceStr(trace, trace_err);
  return (jint)result;
}

void JNICALL Java_com_hesong_ipsc_busnetcli_Client_releaseLibrary(JNIEnv* env,
                                                                  jclass cls) {
  cls_client = NULL;
  SmartBusNetCli_Release();
}

jint JNICALL Java_com_hesong_ipsc_busnetcli_Client_createConnect(
    JNIEnv* env, jclass cls, jbyte local_clientid, jint local_clienttype,
    jstring master_ip, jshort master_port, jstring slaver_ip,
    jshort slaver_port, jstring author_username, jstring author_pwd,
    jstring add_info) {
  jboolean isCopy;
  const char* pc_masterip = env->GetStringUTFChars(master_ip, &isCopy);
  if (!isCopy) throw runtime_error("JNI GetStringUTFChars copy is not made");
  const char* pc_slaverip = env->GetStringUTFChars(slaver_ip, &isCopy);
  if (!isCopy) throw runtime_error("JNI GetStringUTFChars copy is not made");
  const char* pc_author_username =
      env->GetStringUTFChars(author_username, &isCopy);
  if (!isCopy) throw runtime_error("JNI GetStringUTFChars copy is not made");
  const char* pc_author_pwd = env->GetStringUTFChars(author_pwd, &isCopy);
  if (!isCopy) throw runtime_error("JNI GetStringUTFChars copy is not made");
  const char* pc_add_info = env->GetStringUTFChars(add_info, &isCopy);
  if (!isCopy) throw runtime_error("JNI GetStringUTFChars copy is not made");
  int result = SmartBusNetCli_CreateConnect(
      (unsigned char)local_clientid, (int)local_clienttype, pc_masterip,
      (unsigned short)master_port, pc_slaverip, (unsigned short)slaver_port,
      pc_author_username, pc_author_pwd, pc_add_info);
  env->ReleaseStringUTFChars(slaver_ip, pc_masterip);
  env->ReleaseStringUTFChars(slaver_ip, pc_slaverip);
  env->ReleaseStringUTFChars(author_username, pc_author_username);
  env->ReleaseStringUTFChars(author_pwd, pc_author_pwd);
  env->ReleaseStringUTFChars(add_info, pc_add_info);
  return (jint)result;
}

jint JNICALL Java_com_hesong_ipsc_busnetcli_Client_launchFlow(
    JNIEnv* env, jclass cls, jbyte local_client_id, jint server_unit_id,
    jint ipsc_index, jstring project_id, jstring flow_id, jint mode,
    jint timeout, jstring value_list) {
  jboolean isCopy;
  const char* pc_project_id = env->GetStringUTFChars(project_id, &isCopy);
  if (!isCopy) throw runtime_error("JNI GetStringUTFChars copy is not made");
  const char* pc_flow_id = env->GetStringUTFChars(flow_id, &isCopy);
  if (!isCopy) throw runtime_error("JNI GetStringUTFChars copy is not made");
  const char* pc_value_list = env->GetStringUTFChars(value_list, &isCopy);
  if (!isCopy) throw runtime_error("JNI GetStringUTFChars copy is not made");
  int result = SmartBusNetCli_RemoteInvokeFlow(
      (unsigned char)local_client_id, (int)server_unit_id, (int)ipsc_index,
      pc_project_id, pc_flow_id, (int)mode, (int)timeout, pc_value_list);
  env->ReleaseStringUTFChars(project_id, pc_project_id);
  env->ReleaseStringUTFChars(flow_id, pc_flow_id);
  env->ReleaseStringUTFChars(value_list, pc_value_list);
  return (jint)result;
}

jint JNICALL Java_com_hesong_ipsc_busnetcli_Client_sendNotification(
    JNIEnv* env, jclass cls, jbyte local_client_id, jint server_unit_id,
    jint ipsc_index, jstring project_id, jstring title, jint mode, jint expires,
    jstring param) {
  jboolean isCopy;
  const char* pc_project_id = env->GetStringUTFChars(project_id, &isCopy);
  if (!isCopy) throw runtime_error("JNI GetStringUTFChars copy is not made");
  const char* pc_title = env->GetStringUTFChars(title, &isCopy);
  if (!isCopy) throw runtime_error("JNI GetStringUTFChars copy is not made");
  const char* pc_param = env->GetStringUTFChars(param, &isCopy);
  int result = SmartBusNetCli_SendNotify(
      (unsigned char)local_client_id, (int)server_unit_id, (int)ipsc_index,
      pc_project_id, pc_title, (int)mode, (int)expires, pc_param);
  if (!isCopy) throw runtime_error("JNI GetStringUTFChars copy is not made");
  env->ReleaseStringUTFChars(project_id, pc_project_id);
  env->ReleaseStringUTFChars(title, pc_title);
  env->ReleaseStringUTFChars(param, pc_param);
  return (jint)result;
}

jint JNICALL Java_com_hesong_ipsc_busnetcli_Client_sendData(
    JNIEnv* env, jclass cls, jbyte local_client_id, jbyte cmd, jbyte cmd_type,
    jint dst_unit_id, jint dst_client_id, jint dst_client_type,
    jbyteArray data) {
  jsize data_sz = env->GetArrayLength(data);
  jboolean isCopy;
  jbyte* buf = env->GetByteArrayElements(data, &isCopy);
  if (!isCopy) throw runtime_error("JNI GetByteArrayElements copy is not made");
  int result = SmartBusNetCli_SendData(
      (unsigned char)local_client_id, (unsigned char)cmd,
      (unsigned char)cmd_type, (int)dst_unit_id, (int)dst_client_id,
      (int)dst_client_type, (const void*)buf, (int)data_sz);
  env->ReleaseByteArrayElements(data, (jbyte*)buf, 0);
  return (jint)result;
}
