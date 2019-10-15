#pragma once

#include <BLEServer.h>


class StateBleServer: public BLEServerCallbacks {
public:
	StateBleServer();
	~StateBleServer();

private:
	void on_connect(BLEServer* pServer);
	void on_disconnect(BLEServer* pServer);
	bool m_status;
}
