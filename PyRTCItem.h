#include <cnoid/Item>
#include <cnoid/ItemManager>


#include <cnoid/BodyItem>
#include <cnoid/ControllerItem>
#include <cnoid/Body>
#include <cnoid/Light>
#include <cnoid/Archive>




#include "exportdecl.h"










namespace rtmiddleware {


	

	
	class CNOID_EXPORT PyRTCItem : public cnoid::ControllerItem
	{
	public:
		PyRTCItem();
		PyRTCItem(const PyRTCItem& org);
		virtual ~PyRTCItem();
		static void initialize(cnoid::ExtensionManager* ext);
		void setExecContextType(int which);
		void createComp(std::string name);
		void setRelativePathBaseType(int which);

		virtual bool start();
		virtual double timeStep() const;
		virtual void input();
		virtual bool control();
		virtual void output();
		virtual void stop();

		enum RelativePathBaseType {
			RTC_DIRECTORY,
			PROJECT_DIRECTORY,
			N_RELATIVE_PATH_BASE_TYPES
		    };
	    	enum ExecContextType {
	        	PERIODIC_EXECUTION_CONTEXT,
	        	CHOREONOID_EXECUTION_CONTEXT,
	        	N_EXEC_CONTEXT_TYPES
	    	};
	private:
		//controlLink m_crl;
		cnoid::BodyItem* body_item;
		std::string comp_name;
		std::string moduleNameProperty;
		
		cnoid::Selection relativePathBaseType;
		cnoid::Selection execContextType;
		


#ifdef ENABLE_SIMULATION_PROFILING
		virtual void getProfilingNames(std::vector<std::string>& profilingNames){};
		virtual void getProfilingTimes(std::vector<double>& profilingTimes){};
#endif
	protected:
		
		
		virtual void doPutProperties(cnoid::PutPropertyFunction& putProperty);
		virtual cnoid::Item* doDuplicate() const override;
		virtual bool store(cnoid::Archive& archive) override;
		virtual bool restore(const cnoid::Archive& archive) override;
		


		virtual bool initialize(cnoid::ControllerItemIO* io) override;
	    virtual void onPositionChanged();
		


	};

};
