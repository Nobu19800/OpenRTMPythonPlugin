#ifndef RTCEDITORITEM_H
#define RTCEDITORITEM_H

#include <cnoid/Item>
#include <cnoid/ItemManager>
#include <cnoid/CorbaUtil>
#include <cnoid/ControllerItem>



#include <src/OpenRTMPlugin/RTSItem.h>


#include "PyRTCItem.h"
#include "RTC_MainWindow.h"
#include "RTC_XML.h"

#include "exportdecl.h"










namespace rtmiddleware {
	
	class CNOID_EXPORT RTCEditorItem : public PyRTCItemBase
	{
	public:
		RTCEditorItem();
		RTCEditorItem(const RTCEditorItem& org);
		virtual ~RTCEditorItem();
		static void initialize(cnoid::ExtensionManager* ext);
		void onItemSelectionChanged(cnoid::RTSComp* item);
		void createEditComp(std::string name);
		void update_comp(std::string filename);
		void activate_comp();
		void deactivate_comp();
		void reset_comp();
		void get_status(RTC_XML::RTC_ProfileRTP::RTC_State& status);
		void add_dataport(RTC_XML::DataPorts port);


	private:
		cnoid::Connection selectionChangedConnection;
		RTC_MainWindow *mwin;
	protected:
		virtual void doPutProperties(cnoid::PutPropertyFunction& putProperty);
		virtual cnoid::Item* doDuplicate() const override;
		virtual bool store(cnoid::Archive& archive) override;
		virtual bool restore(const cnoid::Archive& archive) override;


		virtual bool initialize(cnoid::ControllerItemIO* io) override;
		virtual void onPositionChanged();


	};

};


#endif