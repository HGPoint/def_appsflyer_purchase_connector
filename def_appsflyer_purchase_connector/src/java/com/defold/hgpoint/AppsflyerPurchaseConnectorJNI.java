package com.defold.hgpoint;

import android.app.Activity;
import android.app.Application;
import android.util.Log;

import com.appsflyer.api.PurchaseClient;
import com.appsflyer.api.Store;

import java.util.HashMap;
import java.util.Map;

public class AppsflyerPurchaseConnectorJNI {

    private String TAG = "AppsflyerPurchaseConnectorJNI";

    private Activity activity;

    private PurchaseClient purchaseClient;
    PurchaseClient.Builder builder;

    Map<String, Object> inAppAdditionalData = new HashMap<String, Object>();
    Map<String, Object> subscriptionAdditionalData = new HashMap<String, Object>();

    public AppsflyerPurchaseConnectorJNI(Activity activity) {
        this.activity = activity;
    }

    private void checkBuilder() {
        if (purchaseClient != null) {
            Log.w(TAG, "Can't change options after initialization");
            return;
        }
        if (builder == null) {
            builder = new PurchaseClient.Builder(activity.getApplicationContext(), Store.GOOGLE);

            builder.setInAppPurchaseEventDataSource(purchaseEvents -> {
                return inAppAdditionalData;
            });

            builder.setSubscriptionPurchaseEventDataSource(purchaseEvents -> {
                return subscriptionAdditionalData;
            });
        }
    }

    private void checkPurchaseClient() {
        if (purchaseClient == null) {
            checkBuilder();
            purchaseClient = builder.build();
            builder = null;
        }
    }

    public void SetIapAdditionalData(String key, String value) {
        inAppAdditionalData.put(key, value);
    }

    public void SetSubscriptionsAdditionalData(String key, String value) {
        subscriptionAdditionalData.put(key, value);
    }

    public void SetSandbox(boolean b) {
        checkBuilder();
        builder.setSandbox(b);
    }

    public void LogSubscriptions(boolean b) {
        checkBuilder();
        builder.logSubscriptions(b);
    }

    public void AutoLogInApps(boolean b) {
        checkBuilder();
        builder.autoLogInApps(b);
    }

    public void StartObservingTransactions() {
        checkPurchaseClient();
        purchaseClient.startObservingTransactions();
    }

    public void StopObservingTransactions() {
        checkPurchaseClient();
        purchaseClient.stopObservingTransactions();
    }
}
