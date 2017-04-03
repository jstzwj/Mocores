#include <fstream>

// 文本方式存档
#include "boost/archive/text_oarchive.hpp"
#include "boost/archive/text_iarchive.hpp"

/////////////////////////////////////////////////////////////
// gps coordinate
//
// illustrates serialization for a simple type
//
class gps_position
{
private:
    friend class boost::serialization::access;//置入式
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & degrees;//序列化或反序列化&操作符比>>和<<更为方便
        ar & minutes;
        ar & seconds;
    }
    int degrees;
    int minutes;
    float seconds;
public:
    gps_position(){}
    gps_position(int d, int m, float s) :
        degrees(d), minutes(m), seconds(s)
    {}
};

int main() {
    std::fstream ofs("filename");

    // create class instance
    const gps_position g(35, 59, 24.567f);

    // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        oa << g;
    }

    // ... some time later restore the class instance to its orginal state
    gps_position newg;
    {
        std::fstream ifs("filename");
        boost::archive::text_iarchive ia(ifs);
        ia >> newg;
    }
    return 0;
}
