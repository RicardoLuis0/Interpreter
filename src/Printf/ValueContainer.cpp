#include "Printf/ValueContainer.h"

using namespace Printf;

std::shared_ptr<ValueContainer> Printf::as_vcp(std::shared_ptr<ValueContainer> p){
    return p;
}
std::shared_ptr<ValueContainer> Printf::as_vcp(float f){
    return std::make_shared<FloatContainerImpl>(f);
}
std::shared_ptr<ValueContainer> Printf::as_vcp(double d){
    return std::make_shared<DoubleContainerImpl>(d);
}
std::shared_ptr<ValueContainer> Printf::as_vcp(int8_t i){
    return std::make_shared<Int8ContainerImpl>(i);
}
std::shared_ptr<ValueContainer> Printf::as_vcp(uint8_t u){
    return std::make_shared<UInt8ContainerImpl>(u);
}
std::shared_ptr<ValueContainer> Printf::as_vcp(int16_t i){
    return std::make_shared<Int16ContainerImpl>(i);
}
std::shared_ptr<ValueContainer> Printf::as_vcp(uint16_t u){
    return std::make_shared<UInt16ContainerImpl>(u);
}
std::shared_ptr<ValueContainer> Printf::as_vcp(int32_t i){
    return std::make_shared<Int32ContainerImpl>(i);
}
std::shared_ptr<ValueContainer> Printf::as_vcp(uint32_t u){
    return std::make_shared<UInt32ContainerImpl>(u);
}
std::shared_ptr<ValueContainer> Printf::as_vcp(int64_t i){
    return std::make_shared<Int64ContainerImpl>(i);
}
std::shared_ptr<ValueContainer> Printf::as_vcp(uint64_t u){
    return std::make_shared<UInt64ContainerImpl>(u);
}
std::shared_ptr<ValueContainer> Printf::as_vcp(const std::string &s){
    return std::make_shared<StringContainerImpl>(s);
}
std::shared_ptr<ValueContainer> Printf::as_vcp(const char * s){
    return std::make_shared<CStringContainerImpl>(s);
}
std::shared_ptr<ValueContainer> Printf::as_vcp(void * p){
    return std::make_shared<PointerContainerImpl>(p);
}

void ValueContainer::dummy(){
    //DO NOTHING
}

FloatContainerImpl::FloatContainerImpl(float f2):f(f2){
    
}

float FloatContainerImpl::getFloat(){
    return f;
}

DoubleContainerImpl::DoubleContainerImpl(double d2):d(d2){
    
}

double DoubleContainerImpl::getDouble(){
    return d;
}

Int8ContainerImpl::Int8ContainerImpl(int8_t i):i8(i){
    
}

int8_t Int8ContainerImpl::getInt8(){
    return i8;
}

UInt8ContainerImpl::UInt8ContainerImpl(uint8_t u):ui8(u){
    
}

uint8_t UInt8ContainerImpl::getUInt8(){
    return ui8;
}

Int16ContainerImpl::Int16ContainerImpl(int16_t i):i16(i){
    
}

int16_t Int16ContainerImpl::getInt16(){
    return i16;
}

UInt16ContainerImpl::UInt16ContainerImpl(uint16_t u):ui16(u){
    
}

uint16_t UInt16ContainerImpl::getUInt16(){
    return ui16;
}

Int32ContainerImpl::Int32ContainerImpl(int32_t i):i32(i){
    
}

int32_t Int32ContainerImpl::getInt32(){
    return i32;
}

UInt32ContainerImpl::UInt32ContainerImpl(uint32_t u):ui32(u){
    
}

uint32_t UInt32ContainerImpl::getUInt32(){
    return ui32;
}

Int64ContainerImpl::Int64ContainerImpl(int64_t i):i64(i){
    
}

int64_t Int64ContainerImpl::getInt64(){
    return i64;
}

UInt64ContainerImpl::UInt64ContainerImpl(uint64_t u):ui64(u){
    
}

uint64_t UInt64ContainerImpl::getUInt64(){
    return ui64;
}

StringContainerImpl::StringContainerImpl(const std::string & s2):s(s2){
    
}

const std::string & StringContainerImpl::getString(){
    return s;
}

CStringContainerImpl::CStringContainerImpl(const char * cs2):cs(cs2){
    
}

const char * CStringContainerImpl::getCString(){
    return cs;
}

PointerContainerImpl::PointerContainerImpl(const void * p2):p(p2){
    
}

const void * PointerContainerImpl::getPointer(){
    return p;
}
