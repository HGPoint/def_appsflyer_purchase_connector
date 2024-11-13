#if defined(DM_PLATFORM_ANDROID) || defined(DM_PLATFORM_IOS)

#pragma once

#include <dmsdk/sdk.h>

namespace dmAppsflyerPurchaseConnector
{
    void Initialize_Ext();
    
    void SetIapAdditionalData(const char* key, const char* value);
    void SetSubscriptionsAdditionalData(const char* key, const char* value);
    void SetSandbox(bool b);
    void LogSubscriptions(bool b);
    void AutoLogInApps(bool b);
    void StartObservingTransactions();
    void StopObservingTransactions();

} // namespace

#endif // platform