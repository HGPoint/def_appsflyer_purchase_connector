#if defined(DM_PLATFORM_IOS)

#include <dmsdk/sdk.h>

#import "appsflyer_purchase_connector.h"

namespace dmAppsflyerPurchaseConnector {
    void Initialize_Ext(){}
    void SetIapAdditionalData(const char* key, const char* value){}
    void SetSubscriptionsAdditionalData(const char* key, const char* value){}
    void SetSandbox(bool b){}
    void LogSubscriptions(bool b){}
    void AutoLogInApps(bool b){}
    void Initialize(){}
    void StartObservingTransactions(){}
    void StopObservingTransactions(){}
} // namespace

#endif // platform