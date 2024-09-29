#include "UnrealGroqBPLibrary.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

#pragma once

float UUnrealGroqBPLibrary::UnrealGroqSampleFunction(float Param)
{
    return -1;
}

FString UUnrealGroqBPLibrary::SendChatMessageToGroq(const FString& ApiKey, const FString& UserMessage, EGroqModel Model, FOnSuccess OnSuccess, FOnFailure OnFailure, FOnProgress OnProgress)
{
    // Create the HTTP request
    TSharedRef<IHttpRequest> Request = FHttpModule::Get().CreateRequest();
    Request->SetURL("https://api.groq.com/openai/v1/chat/completions");
    Request->SetVerb("POST");
    Request->SetHeader("Authorization", "Bearer " + ApiKey);
    Request->SetHeader("Content-Type", "application/json");

    // Prepare the JSON body
    TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
    JsonObject->SetStringField("model", UEnum::GetValueAsString(Model));
    JsonObject->SetStringField("message", UserMessage);

    // Serialize the JSON to a string
    FString JsonString;
    TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&JsonString);
    if (FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer))
    {
        // Set the request body
        Request->SetContentAsString(JsonString);
    }

    // Bind the response handler
    Request->OnProcessRequestComplete().BindLambda([OnSuccess, OnFailure](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
    {
        if (bWasSuccessful && Response.IsValid() && Response->GetResponseCode() == 200)
        {
            // Parse the response (you can customize this based on the API response structure)
            FString ResponseString = Response->GetContentAsString();
            OnSuccess.ExecuteIfBound(ResponseString);
        }
        else
        {
            // Handle failure
            FString ErrorString = Response.IsValid() ? Response->GetContentAsString() : TEXT("Request Failed");
            OnFailure.ExecuteIfBound(ErrorString);
        }
    });

    // Send the request
    Request->ProcessRequest();

    // Return an empty string (or you can return a status message if needed)
    return TEXT("");
}
