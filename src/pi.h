#pragma once

#include "buffer.h"
#include <array>
#include <memory>
#include <string>
#include <boost/asio.hpp>


class AsioData;
class DataReader;
class DataResponse;
class DataWriter;
class Response;
class Session;
class User;


// Protocol interpreter
class PI {
	struct LoginData {
		enum class State {READ_USER, RESP_USER, READ_PASS, RESP_PASS};

		std::string username;
		std::string password;
		State state = State::READ_USER;
		User* user = nullptr;
	};
public:
	PI(Session&);
	~PI() = default;
	void begin(void);
	void resume(void);
	Buffer& getOutputBuffer(void);
private:
	std::shared_ptr<Response> makeResponse(void);
	void setDefaultCallback(std::shared_ptr<Response>&);
	void setDefaultFinishCallback(std::shared_ptr<DataWriter>&);
	void setDefaultFinishCallback(std::shared_ptr<DataReader>&);
	void readCallback(const boost::system::error_code&, std::size_t);
	void writeCallback(const AsioData&, std::shared_ptr<Response>);
	void readCallback(const boost::system::error_code&, std::size_t, std::shared_ptr<LoginData>);
	void writeCallback(const AsioData&, std::shared_ptr<Response>, std::shared_ptr<LoginData>);
	void writeCallback(const AsioData&, std::shared_ptr<DataResponse>);
	void finishCallbackW(const AsioData&, std::shared_ptr<DataResponse>);
	void finishCallbackR(const AsioData&, std::shared_ptr<DataResponse>);
	bool updateReadInput(std::size_t);
	void readSome(void);
	void readSome(std::shared_ptr<LoginData>);
	static std::string getFeaturesResp(void);

	Session& session;
	Buffer inputBuffer;
	Buffer outputBuffer;
	std::string cmdStr;
};


// continue
inline
void PI::resume() {
	readSome();
}


inline
Buffer& PI::getOutputBuffer() {
	return outputBuffer;
}
