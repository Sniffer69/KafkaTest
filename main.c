#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

//Code to convert any string to url format

char* url_encode(const char* str) {
    int len = strlen(str);
    char* out = (char*)malloc(len * 3 + 1); // maximum size required for encoding
    char* p = out;

    for (int i = 0; i < len; i++) {
        if (str[i] == ' ') {
            p += sprintf(p, "%%20");
        }
        else if ((str[i] >= '0' && str[i] <= '9') ||
                 (str[i] >= 'A' && str[i] <= 'Z') ||
                 (str[i] >= 'a' && str[i] <= 'z') ||
                 (str[i] == '-' || str[i] == '_' || str[i] == '.' || str[i] == '~')) {
            *p++ = str[i];
        }
        else {
            p += sprintf(p, "%%%02X", (unsigned char)str[i]);
        }
    }

    *p = '\0'; // terminate the string with a null character
    return out;
}

//main function

int main(){
    CURL *curl;
    CURLcode res;
    char url[1000];
    char input[100];
    printf("Enter a string to URL encode: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // remove newline character if present

    char* output = url_encode(input);
    printf("URL encoded string: %s\n", output);


// Full url to post data
    sprintf(url, "http://localhost:8080/kafka/api/producer?message=%s", output);
    printf("%s\n",url);

// Hit the url
    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, url);
        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(res));
        curl_easy_cleanup(curl);
        free(output);
    }
    return 0;
}
