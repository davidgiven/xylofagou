#pragma once

class Response : public std::stringstream
{
public:
    Response(): _status(200), _contentType("application/json") {}
    Response(const Response&) = delete;
    Response(const Response&&) = delete;

    Response(int status): _status(status), _contentType("text/plain") {}

    void setStatus(int status);
    void outputTo(std::ostream& stream);

private:
    int _status;
    std::string _contentType;
};

static inline std::ostream& operator<<(std::ostream& stream, Response& response)
{
    response.outputTo(stream);
    return stream;
}
