#ifndef VALUECONTAINER_H
#define VALUECONTAINER_H

#include <memory>
#include <cstdint>
#include <string>

namespace Printf {
    class ValueContainer {
        virtual void dummy();
    };
    std::shared_ptr<ValueContainer> as_vcp(std::shared_ptr<ValueContainer>);
    std::shared_ptr<ValueContainer> as_vcp(float);
    std::shared_ptr<ValueContainer> as_vcp(double);
    std::shared_ptr<ValueContainer> as_vcp(int8_t);
    std::shared_ptr<ValueContainer> as_vcp(uint8_t);
    std::shared_ptr<ValueContainer> as_vcp(int16_t);
    std::shared_ptr<ValueContainer> as_vcp(uint16_t);
    std::shared_ptr<ValueContainer> as_vcp(int32_t);
    std::shared_ptr<ValueContainer> as_vcp(uint32_t);
    std::shared_ptr<ValueContainer> as_vcp(int64_t);
    std::shared_ptr<ValueContainer> as_vcp(uint64_t);
    std::shared_ptr<ValueContainer> as_vcp(const std::string &);
    std::shared_ptr<ValueContainer> as_vcp(const char *);
    std::shared_ptr<ValueContainer> as_vcp(void *);
    class Int8Container : public ValueContainer {
    public:
        virtual int8_t getInt8()=0;
    };
    class UInt8Container : public ValueContainer {
    public:
        virtual uint8_t getUInt8()=0;
    };
    class Int16Container : public ValueContainer {
    public:
        virtual int16_t getInt16()=0;
    };
    class UInt16Container : public ValueContainer {
    public:
        virtual uint16_t getUInt16()=0;
    };
    class Int32Container : public ValueContainer {
    public:
        virtual int32_t getInt32()=0;
    };
    class UInt32Container : public ValueContainer {
    public:
        virtual uint32_t getUInt32()=0;
    };
    class Int64Container : public ValueContainer {
    public:
        virtual int64_t getInt64()=0;
    };
    class UInt64Container : public ValueContainer {
    public:
        virtual uint64_t getUInt64()=0;
    };
    class FloatContainer : public ValueContainer {
    public:
        virtual float getFloat()=0;
    };
    class DoubleContainer : public ValueContainer {
    public:
        virtual double getDouble()=0;
    };
    class StringContainer : public ValueContainer {
    public:
        virtual const std::string & getString()=0;
    };
    class CStringContainer : public ValueContainer {
    public:
        virtual const char * getCString()=0;
    };
    class PointerContainer : public ValueContainer {
    public:
        virtual const void * getPointer()=0;
    };
    class FloatContainerImpl : public FloatContainer {
        float f;
    public:
        FloatContainerImpl(float);
        virtual float getFloat() override;
    };
    class DoubleContainerImpl : public DoubleContainer {
        double d;
    public:
        DoubleContainerImpl(double);
        virtual double getDouble() override;
    };
    class Int8ContainerImpl : public Int8Container {
        int8_t i8;
    public:
        Int8ContainerImpl(int8_t);
        virtual int8_t getInt8() override;
    };
    class UInt8ContainerImpl : public UInt8Container {
        uint8_t ui8;
    public:
        UInt8ContainerImpl(uint8_t);
        virtual uint8_t getUInt8() override;
    };
    class Int16ContainerImpl : public Int16Container {
        int16_t i16;
    public:
        Int16ContainerImpl(int16_t);
        virtual int16_t getInt16() override;
    };
    class UInt16ContainerImpl : public UInt16Container {
        uint16_t ui16;
    public:
        UInt16ContainerImpl(uint16_t);
        virtual uint16_t getUInt16() override;
    };
    class Int32ContainerImpl : public Int32Container {
        int32_t i32;
    public:
        Int32ContainerImpl(int32_t);
        virtual int32_t getInt32() override;
    };
    class UInt32ContainerImpl : public UInt32Container {
        uint32_t ui32;
    public:
        UInt32ContainerImpl(uint32_t);
        virtual uint32_t getUInt32() override;
    };
    class Int64ContainerImpl : public Int64Container {
        int64_t i64;
    public:
        Int64ContainerImpl(int64_t);
        virtual int64_t getInt64() override;
    };
    class UInt64ContainerImpl : public UInt64Container {
        uint64_t ui64;
    public:
        UInt64ContainerImpl(uint64_t);
        virtual uint64_t getUInt64() override;
    };
    class StringContainerImpl : public StringContainer {
        const std::string &s;
    public:
        StringContainerImpl(const std::string &s);
        virtual const std::string & getString() override;
    };
    class CStringContainerImpl : public CStringContainer {
        const char * cs;
    public:
        CStringContainerImpl(const char * cs);
        virtual const char * getCString() override;
    };
    class PointerContainerImpl : public PointerContainer {
        const void * p;
    public:
        PointerContainerImpl(const void * p);
        virtual const void * getPointer() override;
    };
}

#endif // VALUECONTAINER_H
