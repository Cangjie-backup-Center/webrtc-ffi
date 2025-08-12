//
// Created on 2025/8/11.
//
// Node APIs are not fully supported. To solve the compilation error of the interface cannot be found,
// please include "napi/native_api.h".

#include "ffi_data_channel.h"
#include "ffi_exception.h"

namespace webrtc {
    ffiDataChannelObserverTemp::ffiDataChannelObserverTemp(rtc::scoped_refptr<DataChannelInterface> dataChannel)
        : dataChannel_(std::move(dataChannel))
    {
        RTC_LOG(LS_VERBOSE) << __FUNCTION__;
        
        dataChannel_->RegisterObserver(this);
    }
    
    ffiDataChannelObserverTemp::~ffiDataChannelObserverTemp()
    {
        RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    
        dataChannel_->UnregisterObserver();
    }
    

// readonly
    std::string ffiDataChannelObserverTemp::GetLabel(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->label();
    }
    bool ffiDataChannelObserverTemp::GetOrdered(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->ordered();
    }
    int64_t ffiDataChannelObserverTemp::GetMaxPacketLifeTime(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->maxPacketLifeTime().value();
    }
    int64_t ffiDataChannelObserverTemp::GetMaxRetransmits(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return  dataChannel_->maxRetransmitsOpt().value();
    }
    std::string ffiDataChannelObserverTemp::GetProtocol(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->protocol();
    }
    bool ffiDataChannelObserverTemp::GetNegotiated(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->negotiated();
    }
    int64_t ffiDataChannelObserverTemp::GetId(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->id();
    }
    FFIDataChannelState ffiDataChannelObserverTemp::GetReadyState(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        switch (dataChannel_->state()) {
            case DataChannelInterface::kConnecting:
                return FFIDataChannelState::CONNECTING;
            case DataChannelInterface::kOpen:
                return FFIDataChannelState::OPEN;
            case DataChannelInterface::kClosing:
                return FFIDataChannelState::CLOSING;
            case DataChannelInterface::kClosed:
                return FFIDataChannelState::CLOSED;
            default:
                break;
        }
        CANGJIE_THROW("Invalid state");
    }
    int64_t ffiDataChannelObserverTemp::GetBufferedAmount(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return dataChannel_->buffered_amount();
    }
    int64_t ffiDataChannelObserverTemp::GetBufferedAmountLowThreshold(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return bufferedAmountLowThreshold_.load();
    }
    void ffiDataChannelObserverTemp::SetBufferedAmountLowThreshold(int64_t value){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        if (value < 0) {
            CANGJIE_THROW("Invalid argument");
        }
        bufferedAmountLowThreshold_.store(value);
    }
    FFIBinaryType ffiDataChannelObserverTemp::GetBinaryType(){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        return binaryType_;
    }
    void ffiDataChannelObserverTemp::SetBinaryType(FFIBinaryType value){
        RTC_DLOG(LS_VERBOSE) << __FUNCTION__;
        binaryType_ = value;
    }
// readonly
    void ffiDataChannelObserverTemp::SetCJClassID(int64_t id){
        cj_class_id_ = id;
    }
    void ffiDataChannelObserverTemp::SetOnStateChange(void (*pe)(int64_t id, int64_t ptr)){
        cj_func_OnStateChange_ = pe;
    }

    void ffiDataChannelObserverTemp::OnStateChange()
    {
        RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    
        auto state = dataChannel_->state();
//        this->PushEvent([](auto state) {
//            
//        });
    }
    
    void ffiDataChannelObserverTemp::OnMessage(const DataBuffer& buffer)
    {
        RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    
        
    }
    
    void ffiDataChannelObserverTemp::OnBufferedAmountChange(uint64_t sentDataSize)
    {
        // should not reached
        (void)sentDataSize;
        RTC_LOG(LS_VERBOSE) << __FUNCTION__;
    }
}