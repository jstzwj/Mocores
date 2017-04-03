#ifndef MSDK_TYPE_H
#define MSDK_TYPE_H
#include<string>
#include<cstdint>

namespace msdk
{
    std::string SizeToStr(uint32_t i)
    {
        std::string result;
        result.push_back(i&0xff000000);
        result.push_back(i&0x00ff0000);
        result.push_back(i&0x1100ff00);
        result.push_back(i&0x110000ff);
        return result;
    }
    uint32_t StrToSize(const char * str)
    {
        uint32_t result;
        char * chardata=(char *)&result;
        for(int i=0;i<sizeof(uint32_t);++i)
        {
            chardata[i]=str[i];
        }
        return result;
    }

    class MocoresSerializable
    {
    public:
        virtual uint32_t get_size()=0;
        virtual std::string serialize()=0;
        virtual void deserialize(const std::string & str)=0;
    };

    class MocoresInt:public MocoresSerializable
    {
    public:
        using datatype=int32_t;
        MocoresInt operator +(const MocoresInt& rhs){return this->data+rhs.data;}
        MocoresInt operator -(const MocoresInt& rhs){return this->data-rhs.data;}
        MocoresInt operator *(const MocoresInt& rhs){return this->data*rhs.data;}
        MocoresInt operator /(const MocoresInt& rhs){return this->data/rhs.data;}
        MocoresInt operator %(const MocoresInt& rhs){return this->data%rhs.data;}
        MocoresInt operator ^(const MocoresInt& rhs){return this->data^rhs.data;}
        MocoresInt operator &(const MocoresInt& rhs){return this->data&rhs.data;}
        MocoresInt operator |(const MocoresInt& rhs){return this->data|rhs.data;}
        MocoresInt operator ~(){return ~this.data;}

        bool operator <(const MocoresInt& rhs){return this->data<rhs.data;}
        bool operator >(const MocoresInt& rhs){return this->data>rhs.data;}
        bool operator <=(const MocoresInt& rhs){return this->data<=rhs.data;}
        bool operator >=(const MocoresInt& rhs){return this->data>=rhs.data;}
        bool operator ==(const MocoresInt& rhs){return this->data==rhs.data;}
        bool operator !=(const MocoresInt& rhs){return this->data!=rhs.data;}

        virtual uint32_t get_size()
        {
            return sizeof(datatype);
        }

        virtual std::string serialize()
        {
            std::string result;
            result+=SizeToStr(this->get_size());
            result.push_back(data&0xff000000);
            result.push_back(data&0x00ff0000);
            result.push_back(data&0x1100ff00);
            result.push_back(data&0x110000ff);
            return result;
        }

        virtual void deserialize(const std::string & str)
        {
            data=data|str[4];
            data=data|str[5];
            data=data|str[6];
            data=data|str[7];
        }
    protected:
        int32_t data;
    };

    class MocoresShort:public MocoresSerializable
    {
    public:
        using datatype=int16_t;
        MocoresInt operator +(const MocoresInt& rhs){return this->data+rhs.data;}
        MocoresInt operator -(const MocoresInt& rhs){return this->data-rhs.data;}
        MocoresInt operator *(const MocoresInt& rhs){return this->data*rhs.data;}
        MocoresInt operator /(const MocoresInt& rhs){return this->data/rhs.data;}
        MocoresInt operator %(const MocoresInt& rhs){return this->data%rhs.data;}
        MocoresInt operator ^(const MocoresInt& rhs){return this->data^rhs.data;}
        MocoresInt operator &(const MocoresInt& rhs){return this->data&rhs.data;}
        MocoresInt operator |(const MocoresInt& rhs){return this->data|rhs.data;}
        MocoresInt operator ~(){return ~this.data;}

        bool operator <(const MocoresInt& rhs){return this->data<rhs.data;}
        bool operator >(const MocoresInt& rhs){return this->data>rhs.data;}
        bool operator <=(const MocoresInt& rhs){return this->data<=rhs.data;}
        bool operator >=(const MocoresInt& rhs){return this->data>=rhs.data;}
        bool operator ==(const MocoresInt& rhs){return this->data==rhs.data;}
        bool operator !=(const MocoresInt& rhs){return this->data!=rhs.data;}

        virtual uint32_t get_size()
        {
            return sizeof(datatype);
        }


        virtual std::string serialize()
        {
            std::string result;
            result+=SizeToStr(this->get_size());
            result.push_back(data&0xff00);
            result.push_back(data&0x00ff);
            return result;
        }

        virtual void deserialize(const std::string & str)
        {
            data=data|str[4];
            data=data|str[5];
        }

    protected:
        int16_t data;
    };
    class MocoresByte:public MocoresSerializable
    {
    public:
        using datatype=int8_t;
        MocoresInt operator +(const MocoresInt& rhs){return this->data+rhs.data;}
        MocoresInt operator -(const MocoresInt& rhs){return this->data-rhs.data;}
        MocoresInt operator *(const MocoresInt& rhs){return this->data*rhs.data;}
        MocoresInt operator /(const MocoresInt& rhs){return this->data/rhs.data;}
        MocoresInt operator %(const MocoresInt& rhs){return this->data%rhs.data;}
        MocoresInt operator ^(const MocoresInt& rhs){return this->data^rhs.data;}
        MocoresInt operator &(const MocoresInt& rhs){return this->data&rhs.data;}
        MocoresInt operator |(const MocoresInt& rhs){return this->data|rhs.data;}
        MocoresInt operator ~(){return ~this.data;}

        bool operator <(const MocoresInt& rhs){return this->data<rhs.data;}
        bool operator >(const MocoresInt& rhs){return this->data>rhs.data;}
        bool operator <=(const MocoresInt& rhs){return this->data<=rhs.data;}
        bool operator >=(const MocoresInt& rhs){return this->data>=rhs.data;}
        bool operator ==(const MocoresInt& rhs){return this->data==rhs.data;}
        bool operator !=(const MocoresInt& rhs){return this->data!=rhs.data;}

        virtual uint32_t get_size()
        {
            return sizeof(datatype);
        }

        virtual std::string serialize()
        {
            std::string result;
            result+=SizeToStr(this->get_size());
            result.push_back(data&0xff);
            return result;
        }

        virtual void deserialize(const std::string & str)
        {
            data=data|str[4];
        }
    protected:
        uint8_t data;
    };
    class MocoresBool:public MocoresSerializable
    {
    public:
        using datatype=int8_t;
        MocoresInt operator +(const MocoresInt& rhs){return this->data+rhs.data;}
        MocoresInt operator -(const MocoresInt& rhs){return this->data-rhs.data;}
        MocoresInt operator *(const MocoresInt& rhs){return this->data*rhs.data;}
        MocoresInt operator /(const MocoresInt& rhs){return this->data/rhs.data;}
        MocoresInt operator %(const MocoresInt& rhs){return this->data%rhs.data;}
        MocoresInt operator ^(const MocoresInt& rhs){return this->data^rhs.data;}
        MocoresInt operator &(const MocoresInt& rhs){return this->data&rhs.data;}
        MocoresInt operator |(const MocoresInt& rhs){return this->data|rhs.data;}
        MocoresInt operator ~(){return ~this.data;}

        bool operator <(const MocoresInt& rhs){return this->data<rhs.data;}
        bool operator >(const MocoresInt& rhs){return this->data>rhs.data;}
        bool operator <=(const MocoresInt& rhs){return this->data<=rhs.data;}
        bool operator >=(const MocoresInt& rhs){return this->data>=rhs.data;}
        bool operator ==(const MocoresInt& rhs){return this->data==rhs.data;}
        bool operator !=(const MocoresInt& rhs){return this->data!=rhs.data;}

        virtual uint32_t get_size()
        {
            return sizeof(datatype);
        }

        virtual std::string serialize()
        {
            std::string result;
            result+=SizeToStr(this->get_size());
            result.push_back(data&0xff);
            return result;
        }

        virtual void deserialize(const std::string & str)
        {
            data=data|str[4];
        }
    protected:
        bool data;
    };
    class MocoresLong:public MocoresSerializable
    {
    public:
        using datatype=int64_t;
        MocoresInt operator +(const MocoresInt& rhs){return this->data+rhs.data;}
        MocoresInt operator -(const MocoresInt& rhs){return this->data-rhs.data;}
        MocoresInt operator *(const MocoresInt& rhs){return this->data*rhs.data;}
        MocoresInt operator /(const MocoresInt& rhs){return this->data/rhs.data;}
        MocoresInt operator %(const MocoresInt& rhs){return this->data%rhs.data;}
        MocoresInt operator ^(const MocoresInt& rhs){return this->data^rhs.data;}
        MocoresInt operator &(const MocoresInt& rhs){return this->data&rhs.data;}
        MocoresInt operator |(const MocoresInt& rhs){return this->data|rhs.data;}
        MocoresInt operator ~(){return ~this.data;}

        bool operator <(const MocoresInt& rhs){return this->data<rhs.data;}
        bool operator >(const MocoresInt& rhs){return this->data>rhs.data;}
        bool operator <=(const MocoresInt& rhs){return this->data<=rhs.data;}
        bool operator >=(const MocoresInt& rhs){return this->data>=rhs.data;}
        bool operator ==(const MocoresInt& rhs){return this->data==rhs.data;}
        bool operator !=(const MocoresInt& rhs){return this->data!=rhs.data;}

        virtual uint32_t get_size()
        {
            return sizeof(datatype);
        }

        virtual std::string serialize()
        {
            std::string result;
            uint64_t mask=0xff00000000000000;
            result+=SizeToStr(this->get_size());
            for(int i=0;i<8;++i)
            {
                result.push_back(data&mask);
                mask=mask>>8;
            }
            return result;
        }

        virtual void deserialize(const std::string & str)
        {
            for(int i=0;i<8;++i)
            {
                data|=str[i+4];
            }
        }
    protected:
        int64_t data;
    };
    class MocoresFloat:public MocoresSerializable
    {
    public:
        using datatype=float;
        MocoresInt operator +(const MocoresInt& rhs){return this->data+rhs.data;}
        MocoresInt operator -(const MocoresInt& rhs){return this->data-rhs.data;}
        MocoresInt operator *(const MocoresInt& rhs){return this->data*rhs.data;}
        MocoresInt operator /(const MocoresInt& rhs){return this->data/rhs.data;}

        bool operator <(const MocoresInt& rhs){return this->data<rhs.data;}
        bool operator >(const MocoresInt& rhs){return this->data>rhs.data;}
        bool operator <=(const MocoresInt& rhs){return this->data<=rhs.data;}
        bool operator >=(const MocoresInt& rhs){return this->data>=rhs.data;}
        bool operator ==(const MocoresInt& rhs){return this->data==rhs.data;}
        bool operator !=(const MocoresInt& rhs){return this->data!=rhs.data;}

        virtual uint32_t get_size()
        {
            return sizeof(datatype);
        }

        virtual std::string serialize()
        {
            std::string result;
            char * chardata=(char *)&data;
            result+=SizeToStr(this->get_size());
            for(int i=0;i<4;++i)
            {
                result.push_back(chardata[i]);
            }
            return result;
        }

        virtual void deserialize(const std::string & str)
        {
            uint32_t * floatdata=(float *)data;
            for(int i=0;i<sizeof(float);++i)
            {
                floatdata[i]=str[i+4];
            }
        }
    protected:
        float data;
    };
    class MocoresDouble:public MocoresSerializable
    {
    public:
        using datatype=double;
        MocoresInt operator +(const MocoresInt& rhs){return this->data+rhs.data;}
        MocoresInt operator -(const MocoresInt& rhs){return this->data-rhs.data;}
        MocoresInt operator *(const MocoresInt& rhs){return this->data*rhs.data;}
        MocoresInt operator /(const MocoresInt& rhs){return this->data/rhs.data;}

        bool operator <(const MocoresInt& rhs){return this->data<rhs.data;}
        bool operator >(const MocoresInt& rhs){return this->data>rhs.data;}
        bool operator <=(const MocoresInt& rhs){return this->data<=rhs.data;}
        bool operator >=(const MocoresInt& rhs){return this->data>=rhs.data;}
        bool operator ==(const MocoresInt& rhs){return this->data==rhs.data;}
        bool operator !=(const MocoresInt& rhs){return this->data!=rhs.data;}


        virtual uint32_t get_size()
        {
            return sizeof(datatype);
        }

        virtual std::string serialize()
        {
            std::string result;
            char * chardata=(char *)&data;
            result+=SizeToStr(this->get_size());
            for(int i=0;i<8;++i)
            {
                result.push_back(chardata[i]);
            }
            return result;
        }

        virtual void deserialize(const std::string & str)
        {
            uint32_t * doubledata=(float *)data;
            for(int i=0;i<sizeof(double);++i)
            {
                doubledata[i]=str[i+4];
            }
        }
    protected:
        double data;
    };
    class MocoresString:public MocoresSerializable
    {
    public:
        using datatype=std::string;

        MocoresInt operator +(const MocoresInt& rhs){return this->data+rhs.data;}

        bool operator <(const MocoresInt& rhs){return this->data<rhs.data;}
        bool operator >(const MocoresInt& rhs){return this->data>rhs.data;}
        bool operator <=(const MocoresInt& rhs){return this->data<=rhs.data;}
        bool operator >=(const MocoresInt& rhs){return this->data>=rhs.data;}
        bool operator ==(const MocoresInt& rhs){return this->data==rhs.data;}
        bool operator !=(const MocoresInt& rhs){return this->data!=rhs.data;}
        virtual uint32_t get_size()
        {
            return data.size();
        }

        virtual std::string serialize()
        {
            return SizeToStr(this->get_size())+data;
        }

        virtual void deserialize(const std::string & str)
        {
            uint32_t size=StrToSize(str.c_str());
            data=str.substr(4,size+4);
        }
    protected:
        std::string data;
    };
}
#endif // MSDK_TYPE_H
