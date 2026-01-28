#ifndef APP_HPP
#define APP_HPP

#ifdef __cplusplus
extern "C" {
#endif

void App_Init(void);

#ifdef __cplusplus
}
#endif


template<typename T>
T App_ProcessData(T data)
{
    // Process the data (example implementation)
    T processedData = data * 2; // Just an example operation
    // You can add more complex processing logic here
    return processedData;
}



#endif // APP_HPP

