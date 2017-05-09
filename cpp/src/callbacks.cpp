#include "callbacks.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <jni.h>
#include <pthread.h>

#define GCC_VERSION (__GNUC__ * 10000 \
                     + __GNUC_MINOR__ * 100 \
                     + __GNUC_PATCHLEVEL__)
#if GCC_VERSION >= 40500
  #include <exception>
#else
  #include <stdexcept>
#endif

#include "globvars.h"

using namespace std;

static inline JNIEnv* get_current_thread_env() {
        JNIEnv* env = NULL;
        char err_buf[64] = { 0 };
        jint err = jvm->GetEnv((void**) (&env), JNI_VERSION_1_8);
        switch (err) {
        case JNI_EDETACHED:
                err = jvm->AttachCurrentThread((void**) (&env), NULL);
                if (err != JNI_OK) {
                        snprintf(err_buf, 64, "AttachCurrentThread failed, JNI error code %d", err);
                        throw runtime_error(err_buf);
                }
                break;
        case JNI_EVERSION:
                throw runtime_error("AttachCurrentThread failed, JNI_EVERSION");
                break;
        case JNI_OK:
                break;
        default:
                snprintf(err_buf, 64, "GetEnv failed, JNI error code %d", err);
                throw runtime_error(err_buf);
                break;
        }
        return env;
}

static inline void trace_log(const char * msg, bool is_err) {
        if (!msg)
                return;
        if (!msg[0])
                return;
        size_t msg_sz = strlen(msg);
        if (!msg_sz)
                return;
        JNIEnv* env = get_current_thread_env();
        jbyteArray jbytes_msg = env->NewByteArray(msg_sz);
        env->SetByteArrayRegion(jbytes_msg, 0, msg_sz, (jbyte*) msg);
        env->CallStaticVoidMethod(cls_client, meth_client_log, jbytes_msg, (jboolean) is_err);
        env->ReleaseByteArrayElements(jbytes_msg, (jbyte*) msg, JNI_COMMIT);
}

void connection(void * arg, unsigned char local_client_id,
                int accesspoint_unit_id, int ack) {
        pthread_t self_thread = pthread_self();
        char buf [64] = {0};
        snprintf(buf, 64, "<thread %lu> >>> connection(%x, %d, %d)", self_thread, local_client_id, accesspoint_unit_id, ack);
        trace(buf);
        JNIEnv* env = get_current_thread_env();
        env->CallStaticVoidMethod(
                cls_client, meth_client_connect, (jbyte) local_client_id, (jint) accesspoint_unit_id, (jint) ack
                );
        memset(buf, 0, 64);
        snprintf(buf, 64, "<thread %lu> <<< connection(%x, %d, %d)", self_thread, local_client_id, accesspoint_unit_id, ack);
        trace(buf);
}

void disconnect(void * arg, unsigned char local_client_id) {
        pthread_t self_thread = pthread_self();
        char buf [64] = {0};
        snprintf(buf, 64, "<thread %lu> >>> disconnect(%p, %x)", self_thread, arg, local_client_id);
        trace(buf);
        JNIEnv* env = get_current_thread_env();
        env->CallStaticVoidMethod(cls_client, meth_client_disconnect, (jbyte) local_client_id);
        memset(buf, 0, 64);
        snprintf(buf, 64, "<thread %lu> <<< disconnect(%p, %x)", self_thread, arg, local_client_id);
        trace(buf);
}

void recvdata(void * arg, unsigned char local_client_id,
              SMARTBUS_PACKET_HEAD * head, void * data, int size) {
        JNIEnv* env = get_current_thread_env();
        jbyteArray jbytes_data = env->NewByteArray(size);
        env->SetByteArrayRegion(jbytes_data, 0, size, (jbyte*) data);
        env->CallStaticVoidMethod(
                cls_client, meth_client_recvdata,
                (jbyte) head->cmd, (jbyte) head->cmdtype,
                (jbyte) head->src_unit_id, (jbyte) head->src_unit_client_id, (jbyte) head->src_unit_client_type,
                (jbyte) head->dest_unit_id, (jbyte) head->dest_unit_client_id, (jbyte) head->dest_unit_client_type,
                jbytes_data
                );
        env->ReleaseByteArrayElements(jbytes_data, (jbyte*) data, JNI_COMMIT);
}

void global_connect(void * arg, char unit_id, char client_id, char client_type,
                    char accesspoint_unit, char status, const char * add_info) {
        pthread_t self_thread = pthread_self();
        char buf_log [128] = {0};
        snprintf(buf_log, 128, "<thread %lu> >>> global_connect(%p, %x, %x, %x, %x, %x, %s)", self_thread, arg, unit_id, client_id, client_type, accesspoint_unit, status, add_info);
        trace(buf_log);
        if (!add_info)
                return;
        if (!add_info[0])
                return;
        size_t msg_sz = strlen(add_info);
        if (!msg_sz)
                return;
        char* buf = (char*)calloc(msg_sz + 1, sizeof(char));
        strcpy(buf, add_info);
        JNIEnv* env = get_current_thread_env();
        jstring txt = env->NewStringUTF(buf);
        env->CallStaticVoidMethod(
                cls_client, meth_client_globalconenct,
                (jbyte) unit_id, (jbyte) client_id, (jbyte) client_type,
                (jbyte) status, txt
                );
        env->ReleaseStringUTFChars(txt, buf);
        memset(buf_log, 0, 128);
        snprintf(buf_log, 128, "<thread %lu> <<< global_connect(%p, %x, %x, %x, %x, %x, %s)", self_thread, arg, unit_id, client_id, client_type, accesspoint_unit, status, add_info);
        trace(buf_log);
}

void trace(const char * msg) {
        trace_log(msg, false);
}

void trace_err(const char * msg) {
        trace_log(msg, true);
}
