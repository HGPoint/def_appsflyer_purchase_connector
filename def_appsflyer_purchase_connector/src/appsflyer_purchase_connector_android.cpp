#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/dlib/android.h>

#include "appsflyer_purchase_connector.h"

namespace dmAppsflyerPurchaseConnector {

  struct PurchaseConnector {
    jobject m_PurchaseConnectorJNI;
    jmethodID m_SetIapAdditionalData;
    jmethodID m_SetSubscriptionsAdditionalData;
    jmethodID m_SetSandbox;
    jmethodID m_LogSubscriptions;
    jmethodID m_AutoLogInApps;
    jmethodID m_StartObservingTransactions;
    jmethodID m_StopObservingTransactions;
  };

  static PurchaseConnector g_PurchaseConnector;

  static void InitJNIMethods(JNIEnv * env, jclass cls) {    
    g_PurchaseConnector.m_SetIapAdditionalData = env -> GetMethodID(cls, "SetIapAdditionalData", "(Ljava/lang/String;Ljava/lang/String;)V"); //https://docs.oracle.com/javase/7/docs/technotes/guides/jni/spec/types.html
    g_PurchaseConnector.m_SetSubscriptionsAdditionalData = env -> GetMethodID(cls, "SetSubscriptionsAdditionalData", "(Ljava/lang/String;Ljava/lang/String;)V");
   
    g_PurchaseConnector.m_SetSandbox = env -> GetMethodID(cls, "SetSandbox", "(Z)V");
    g_PurchaseConnector.m_LogSubscriptions = env -> GetMethodID(cls, "LogSubscriptions", "(Z)V");
    g_PurchaseConnector.m_AutoLogInApps = env -> GetMethodID(cls, "AutoLogInApps", "(Z)V");

    g_PurchaseConnector.m_StartObservingTransactions = env -> GetMethodID(cls, "StartObservingTransactions", "()V");
    g_PurchaseConnector.m_StopObservingTransactions = env -> GetMethodID(cls, "StopObservingTransactions", "()V");
  }

  void Initialize_Ext() {
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv * env = threadAttacher.GetEnv();
    jclass cls = dmAndroid::LoadClass(env, "com.defold.hgpoint.AppsflyerPurchaseConnectorJNI");
    InitJNIMethods(env, cls);
    jmethodID jni_constructor = env -> GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");
    g_PurchaseConnector.m_PurchaseConnectorJNI = env -> NewGlobalRef(env -> NewObject(cls, jni_constructor, threadAttacher.GetActivity() -> clazz));
  }

  void StartObservingTransactions() {
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv * env = threadAttacher.GetEnv();
    env -> CallVoidMethod(g_PurchaseConnector.m_PurchaseConnectorJNI, g_PurchaseConnector.m_StartObservingTransactions);
  }

  void StopObservingTransactions() {
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv * env = threadAttacher.GetEnv();
    env -> CallVoidMethod(g_PurchaseConnector.m_PurchaseConnectorJNI, g_PurchaseConnector.m_StopObservingTransactions);
  }

  void SetSandbox(bool cbool) {
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv * env = threadAttacher.GetEnv();
    env -> CallVoidMethod(g_PurchaseConnector.m_PurchaseConnectorJNI, g_PurchaseConnector.m_SetSandbox, cbool);
  }

  void LogSubscriptions(bool cbool) {
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv * env = threadAttacher.GetEnv();
    env -> CallVoidMethod(g_PurchaseConnector.m_PurchaseConnectorJNI, g_PurchaseConnector.m_LogSubscriptions, cbool);
  }

  void AutoLogInApps(bool cbool) {
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv * env = threadAttacher.GetEnv();
    env -> CallVoidMethod(g_PurchaseConnector.m_PurchaseConnectorJNI, g_PurchaseConnector.m_AutoLogInApps, cbool);
  }

  void SetIapAdditionalData(const char * key,
    const char * value) {
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv * env = threadAttacher.GetEnv();
    jstring jkey = env -> NewStringUTF(key);
    jstring jvalue = env -> NewStringUTF(value);
    env -> CallVoidMethod(g_PurchaseConnector.m_PurchaseConnectorJNI, g_PurchaseConnector.m_SetIapAdditionalData, jkey, jvalue);
    env -> DeleteLocalRef(jkey);
    env -> DeleteLocalRef(jvalue);
  }

  void SetSubscriptionsAdditionalData(const char * key,
    const char * value) {
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv * env = threadAttacher.GetEnv();
    jstring jkey = env -> NewStringUTF(key);
    jstring jvalue = env -> NewStringUTF(value);
    env -> CallVoidMethod(g_PurchaseConnector.m_PurchaseConnectorJNI, g_PurchaseConnector.m_SetSubscriptionsAdditionalData, jkey, jvalue);
    env -> DeleteLocalRef(jkey);
    env -> DeleteLocalRef(jvalue);
  }

} // namespace

#endif // platform