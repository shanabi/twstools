#ifndef TWS_DL_H
#define TWS_DL_H

#include "properties.h"

#include <QtCore/QList>




class TWSClient;

namespace IB {
	class ContractDetails;
	class Contract;
}






class ContractDetailsRequest;
class HistRequest;
class GenericRequest;
class WorkTodo;
class ContractDetailsTodo;
class HistTodo;
class PacketContractDetails;
class PacketHistData;
class PacingGod;
class DataFarmStates;


class PropTwsDL : public PropSub
{
	public:
		PropTwsDL( const Properties& prop, const std::string& cName = "" );
		
		void initDefaults();
		bool readProperties();
		
		// fields
		std::string twsHost;
		quint16 twsPort;
		int     clientId;
		
		int conTimeout;
		int reqTimeout;
		int maxRequests;
		int pacingInterval;
		int minPacingTime;
		int violationPause;
		
		bool printFormatDates;
};



class TwsDlWrapper;


class TwsDL
{
	public:
		enum State {
			CONNECT,
			WAIT_TWS_CON,
			IDLE,
			WAIT_DATA,
			QUIT_READY,
			QUIT_ERROR
		};
		
		TwsDL( const QString& confFile, const QString& workFile );
		~TwsDL();
		
		void start();
		
		State currentState() const;
		
	private:
		void initProperties();
		void initTwsClient();
		void eventLoop();
		
		void dumpWorkTodo() const;
		
		void connectTws();
		void waitTwsCon();
		void idle();
		void getContracts();
		void finContracts();
		void getData();
		void waitData();
		void waitContracts();
		void waitHist();
		void finData();
		void onQuit( int ret );
		
		void changeState( State );
		
		void initWork();
		
		void reqContractDetails( const ContractDetailsRequest& );
		void reqHistoricalData( const HistRequest& );
		
		void errorContracts(int, int, const QString &);
		void errorHistData(int, int, const QString &);
		
		// callbacks from our twsWrapper
		void twsError(int, int, const QString &);
		
		void twsConnected( bool connected );
		void twsContractDetails( int reqId,
			const IB::ContractDetails &ibContractDetails );
		void twsBondContractDetails( int reqId,
			const IB::ContractDetails &ibContractDetails );
		void twsContractDetailsEnd( int reqId );
		void twsHistoricalData( int reqId, const QString &date, double open, double high, double low,
			double close, int volume, int count, double WAP, bool hasGaps );
		
		
		State state;
		qint64 lastConnectionTime;
		bool connection_failed;
		int curIdleTime;
		
		QString confFile;
		QString workFile;
		PropTwsDL *myProp;
		
		TwsDlWrapper *twsWrapper;
		TWSClient  *twsClient;
		
		int msgCounter;
		GenericRequest &currentRequest;
		
		int curIndexTodoContractDetails;
		
		WorkTodo *workTodo;
		
		PacketContractDetails &p_contractDetails;
		PacketHistData &p_histData;
		
		DataFarmStates &dataFarms;
		PacingGod &pacingControl;
		
	friend class TwsDlWrapper;
};




#endif
