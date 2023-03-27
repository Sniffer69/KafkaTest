#include <iostream>
#include <curl/curl.h>


int main() {
    CURL *curl;
    CURLcode res;

    // Initialize cURL
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    if (curl) {
        std::string input;
        std::cout << "Enter your input: ";
        std::getline(std::cin, input);
        std::string rep = "%20";
        for(int i=0 ; i<input.length() ; i++)
        {
            if(input[i] == ' ')
                input.replace(i,1,rep);
        }
        std::string baseurl = "http://localhost:8080/kafka/api/producer?message=" + input;
        std::cout<< baseurl;

        // Set the URL to which the request will be sent
        curl_easy_setopt(curl, CURLOPT_URL, baseurl.c_str());

        // Set the POST data
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, input.c_str());

        // Perform the request
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup
        curl_easy_cleanup(curl);
    }

    // Cleanup global cURL resources
    curl_global_cleanup();
    return 0;
}