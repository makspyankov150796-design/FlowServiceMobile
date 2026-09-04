//---------------------------------------------------------------------------

#ifndef TFlowMeterH
#define TFlowMeterH

 #include <System.JSON.hpp>
#include "TFlowMeterType.h"
#include <System.Math.hpp>

 #include <time.h>
  #include <System.DateUtils.hpp >

#include <vector>

#include "TOrderClass.h"
#include "TMeterValue.h"


#include <REST.Client.hpp>
#include <REST.Response.Adapter.hpp>
#include <REST.Types.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Rtti.hpp>
 #include "UserRoutines.h"

#include "TSettingsClass.h"

//---------------------------------------------------------------------------

#define CHANNEL 2
#define XMLVERFLOWMETERS "5.0"




typedef struct TCalibrPoint
{
  	uint8_t   Index;
    tPoint 	*Point;
    double	  Q;             //расход эталонный, чтобы не считать каждый раз   СПРАВОЧНО
    double	  Qtest;          //расход поверяемого прибора, чтобы не считать каждый раз СПРАВОЧНО
   	double     EtlVolume;     //Объем эталона     ОСНОВНОЕ
  	double     Volume;        //Объем прибора     СПРАВОЧНО
  	double	  Time;          //Время измерения   ОСНОВНОЕ
  	double	  Imp;           //Кол-во импульсов  ОСНОВНОЕ
    double     Coef;  //Коэф                      ОСНОВНОЕ
 	uint8_t   State;         //<Состоние
  	System::UnicodeString   Date;  //дата и время измерения
    double     Error;      //Погрешность  измерениы СПРАВОЧНО
    double     Rate;      //Погрешность  измерениы СПРАВОЧНО
}tCalibrPoint;

     typedef struct TCoef
{
  	uint8_t   Index;
    double	  Q1;     //
    double	  Q2;     //
   	double     K;     //
  	double     b;    //

}tCoef;


class TFlowMeter : public TObject
{
	public:

	TFlowMeter(THscDevice *HSCDevice, int ID_Order, bool IsEtalon);
	TFlowMeter(THscDevice *HSCDevice, bool IsEtalon);
	TFlowMeter(bool IsEtalon);
	virtual __fastcall ~TFlowMeter();

        void SetHSC(THscDevice *HSCDevice) {HSCDevice = this->HSCDevice;};

    TFlowMeterType *Type;

	void SetType (TFlowMeterType *Type);
	bool SetType (int typeHash);

	int Hash;
	int DeviceHash;
    int TypeHash;

    bool IsEtalon;
    int  Active;

    int CheckType;

	int Status = 0; // 0 - Создан , 1 - Есть данные, 1 - Есть данные, не годен,
				// 2 - Есть данные, годен,
	UnicodeString GetStatus();

	int SendStatus=0;   // 0 - не отправлен 1- отправляется  2- отправлен
	UnicodeString GetSendStatus();

	   void	SetSendStatus(UnicodeString text);


	UnicodeString Name;

	//
	// Тип поверяемого устройства
	UnicodeString DeviceType;
    UnicodeString Modifications;
	UnicodeString Modification;
	int ID_Order;
	int  VerificationInterval;
	UnicodeString miOwner;
	//
	// Серийный номер поверяемого устройства
	UnicodeString SerialNum;
	//
	// Номер ГРСИ поверяемого устройства
	UnicodeString CertificateNum;

	UnicodeString DN;
	UnicodeString docTitle;

    UnicodeString Adress;

	UnicodeString doc_number;
	static UnicodeString sign_cipher;
	static UnicodeString porveritel_fio;

	UnicodeString means;

	UnicodeString year_production;

	UnicodeString K1,P1,K2,P2;

	UnicodeString tempWater, temperature, pressure, hymidity;

	UnicodeString vrfDate;
	UnicodeString validDate;

	UnicodeString Data1, Data2, Data3;

	UnicodeString Date1, Date2;

	UnicodeString Result = "-";

	TDateTime DateTime;    //дата и время измерения

	//
	// Коэффициент преобразования
	double Kp;

	//
	// Калибровочные коэфициенты
	double K[100];
	double Q[100];

	//Настройки прибора

	double Qmax;
	double Qmin;

	//Текущий расход
	double Flow (void);      // Расход с поправками
	double GetRawFlow(void); // Расход без поправок

	//Текущий объем
	double Volume(void);


	//

	uint8_t GetChannel(void);
	void SetChannel(uint8_t Channel);

	double GetImpKoef(void){return Kp;};
	double GetImpCoef(void){return Kp;};
	double GetKoef(void) {return Kp;};
	UnicodeString GetKoefStr(void) {return FloatToStr(Kp);};
	void SetKoef(double K) {Kp=K;};
	void SaveCoef(void);
	void SetImpKoef(double K){Kp=K;};


	double GetVolume(void);
	double GetFlow(void);
	double GetTime(void);
	double GetTotalImp(void);

	double GetRawWidthFlow(void);
	double GetWidthFlow(void);
	double GetWidthFlowVolume(void);

	double GetFinalVolume(void);
	double GetFinalRawVolume(void);

	double GetFinalFlow(void);
	double GetFinalRawFlow(void);

    int GetRawSecImp(void);

	void ResetTest(void);
	double GetFlowVolume(void);

	double GetFinalImp(void);

	void ReadPIN(void);
	void SavePIN(uint8_t pin);

	void RestoreTypePoints(void);


	void WritePIN(uint8_t pin);

	void  Write_Channel_State(uint16_t State);


	uint8_t AddPointData (UnicodeString Name, double Qrate, double Q, double Volume, double vTime, double Error, double RageMinus,double RagePlus);

	void AddPoint(tPoint Pnt);
	void AddCurrPoint(tPoint Pnt);
	void ClearPoints(void);

	tPoint GetCurrentPoint();
	tPoint SetNextPoint();
	tPoint SetPreviousPoint();



	void SaveDataPoint(TFlowMeter *Etalon);
	tDataPoint GetDataPoint(void) {return DataPoint;}
	void AddDataPoint(tPoint Pnt);



	int8_t AddCalibrPoint(tCalibrPoint Pnt);
	void ClearCalibrPoint(tCalibrPoint Pnt);
	void AddCurrentCalibrPoint(void);
	void AddDataCalibrPoint(void);
	double Rate(double Q);

	void ClearCalibraion(void);

	void SaveCalibrData(void);
	void LoadCalibrData(void);

	int8_t UpdateCoefs(void);

	int8_t AddCalibrData(double vEtlVolume, double vTime, double vImp, double vCoef);



	 tPoint 				Point;
	 tDataPoint 			DataPoint;
	 tCalibrPoint           CalibrPoint;
	 tCoef                  Coef;

	 vector <tPoint> 		Points;
	 vector <tDataPoint> 	DataPoints;
	 vector <tDataPoint> 	UsedDataPoints;
     vector <tCalibrPoint>  CalibrPoints;
     vector <tCoef>   		Coefs;

     // Обратные функции обновления состояния

     void  __fastcall OnConfigRead(TObject * Sender);

     int PointIndex;



    static TXMLDocument *XmlDoc;
    static _di_IXMLNode rootNode;
  	static _di_IXMLNode sampleNode;
    static _di_IXMLNode sampleNode2;
	static _di_IXMLNode sampleNode3;
	static  UnicodeString dirName;
	static  System::UnicodeString fname;


	static  TJSONValue *jValue;
	static  TJSONArray *jArray;
	static  TJSONObject *jObject ;

	static void SaveToFile(TFlowMeter *FlowMeter, int IsBackUp);
	static TFlowMeter * LoadFromFile(void);
	static TFlowMeter * LoadFromFile(THscDevice *HSCDevice);

	static TFlowMeter* GetDevice (int Hash);

	static UnicodeString JSonConvert(TFlowMeter *AFlowMeter);

	static UnicodeString ApiConvert();

	static void ApiSent();
	static  int ApiCheckResult();

	UnicodeString JSonConvert();


	UnicodeString StringStreamConvert();

	void AddToList (void);


	 static vector <TFlowMeter*> FlowMeters;
	 static std::vector<TFlowMeter*>::iterator fit;

	 static std::vector<tPoint>::iterator it;

	 static void StaticInit(THscDevice *HSCDev);
	 static  THscDevice *sHSC;
	 static  TFlowMeter *ActiveFlowMeter;

	 static bool InitType(TFlowMeter* FM);

	static int GetCountInOrder(int iD_Order);

	 TMeterValue *FlowValue;
	 TMeterValue *VolumeValue;
	 TMeterValue *ImpValue;
	 TMeterValue *VolumeErrorValue;

	 void  SetValues(void);
	 void  SetMonitorValues(void);
	 void  SetFinalValues(void);

	 double GetVolumeError();

	 void SetEtalon(TFlowMeter*);
	 void SetAsEtalon(void);
	 bool IsFlowInPoint(double Q);
	 bool IsFlowInPoint(double Q, tPoint point);
	 bool IsDataPointGood(tDataPoint &dataPoint, tPoint point);

	void SortDataPoints(int maxmin);
    vector <tDataPoint> SortDataVector(vector <tDataPoint> vect, int State,int State2,int maxmin);

	 bool GetPointUseFlow(double Q, tPoint &point);

	 int TimeToEndVolumeLimit(double pointVolume, double DelayCoef, double TimeCoef);

	 int CheckStatus();
	 int CheckFullStatus();
	 void IncImpSumMonitor(void);



  protected:

  private:

     uint8_t Channel;
     THscDevice *HSCDevice, *HSC;

	 TFlowMeter* EtalonMeter;

     //архив последних 100 секунд импульсов
     uint16_t Impulses[100];
     uint8_t wr_imp; // индекс записи в архив
     uint8_t rd_imp; // индекс чтения из архива

     double VolSum, ImpSum;

     void Init(bool IsEtalon);


 };



#endif
