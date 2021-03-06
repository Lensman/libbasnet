#include <boost/thread/mutex.hpp>
class Output2FILE
{
public:
    static void Output(const std::string& msg);
    static void SetStream(FILE* pFile);
private:
    static FILE*& StreamImpl();
    static boost::mutex mtx;
};
 
inline FILE*& Output2FILE::StreamImpl()
{
    static FILE* pStream = stderr;
    return pStream;
}
inline void Output2FILE::SetStream(FILE* pFile)
{
    boost::mutex::scoped_lock lock(mtx);
    StreamImpl() = pFile;
}
inline void Output2FILE::Output(const std::string& msg)
{
    boost::mutex::scoped_lock lock(mtx);
    FILE* pStream = StreamImpl();
    if (!pStream)
        return;
    fprintf(pStream, "%s", msg.c_str());
    fflush(pStream);
}