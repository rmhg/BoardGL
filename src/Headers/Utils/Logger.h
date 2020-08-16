#pragma once

class Log : public FileInterface {
private :
	std::string default;
public :
	Log(const std::string&);
	void LogStr(const std::string&);
	void LogPair(const std::string&, const std::string&);
	void DefaultLog();
};

Log::Log(const std::string&) {}
void Log::LogStr(const std::string&) {}
void Log::LogPair(const std::string) {}