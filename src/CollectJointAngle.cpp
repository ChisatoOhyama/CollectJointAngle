// -*- C++ -*-
/*!
 * @file  CollectJointAngle.cpp
 * @brief ModuleDescription
 * @date $Date$
 *
 * $Id$
 */

#include "CollectJointAngle.h"

// Module specification
// <rtc-template block="module_spec">
static const char* collectjointangle_spec[] =
  {
    "implementation_id", "CollectJointAngle",
    "type_name",         "CollectJointAngle",
    "description",       "ModuleDescription",
    "version",           "1.0.0",
    "vendor",            "pretty",
    "category",          "Category",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
CollectJointAngle::CollectJointAngle(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    m_targetJointAngle_HeadIn("targetJointAngle_Head", m_targetJointAngle_Head),
    m_targetJointAngle_LArmIn("targetJointAngle_LArm", m_targetJointAngle_LArm),
    m_targetJointAngle_RArmIn("targetJointAngle_RArm", m_targetJointAngle_RArm),
    m_targetJointAngle_LegIn("targetJointAngle_Leg", m_targetJointAngle_Leg),
    m_targetJointAngle_AllOut("targetJointAngle_All", m_targetJointAngle_All)

    // </rtc-template>
{
}

/*!
 * @brief destructor
 */
CollectJointAngle::~CollectJointAngle()
{
}



RTC::ReturnCode_t CollectJointAngle::onInitialize()
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
  addInPort("targetJointAngle_Head", m_targetJointAngle_HeadIn);
  addInPort("targetJointAngle_LArm", m_targetJointAngle_LArmIn);
  addInPort("targetJointAngle_RArm", m_targetJointAngle_RArmIn);
  addInPort("targetJointAngle_Leg", m_targetJointAngle_LegIn);
  
  // Set OutPort buffer
  addOutPort("targetJointAngle_All", m_targetJointAngle_AllOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

  // <rtc-template block="bind_config">
  // </rtc-template>
  
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CollectJointAngle::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CollectJointAngle::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CollectJointAngle::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t CollectJointAngle::onActivated(RTC::UniqueId ec_id)
{
	for (int i = 0; i < 17; i++){
		m_targetJointAngle_All.data[i] = 0;
	}
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CollectJointAngle::onDeactivated(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}


RTC::ReturnCode_t CollectJointAngle::onExecute(RTC::UniqueId ec_id)
{
	//HeadYaw, HeadPitch, LShoulderPitch, LShoulderRoll, LElbowYaw, LElbowRoll, LWristYaw, LHand, HipRoll, HipPitch, KneePitch, RShoulderPitch, RShoulderRoll, RElbowYaw, RElbowRoll, RWristYaw, RHand

	if (m_targetJointAngle_HeadIn.isNew()){
		m_targetJointAngle_HeadIn.read();
		m_targetJointAngle_All.data[0] = m_targetJointAngle_Head.data[0];
		m_targetJointAngle_All.data[1] = m_targetJointAngle_Head.data[1];
	}
	if (m_targetJointAngle_LArmIn.isNew()){
		m_targetJointAngle_LArmIn.read();
		for (int i = 0; i < 6; i++){
			m_targetJointAngle_All.data[i + 2] = m_targetJointAngle_LArm.data[i];
		}
	}
	if (m_targetJointAngle_RArmIn.isNew()){
		m_targetJointAngle_RArmIn.read();
		for (int i = 0; i < 6; i++){
			m_targetJointAngle_All.data[i + 11] = m_targetJointAngle_RArm.data[i];
		}
	}
	if (m_targetJointAngle_LegIn.isNew()){
		m_targetJointAngle_LegIn.read();
		m_targetJointAngle_All.data[8] = m_targetJointAngle_Leg.data[0];
		m_targetJointAngle_All.data[9] = m_targetJointAngle_Leg.data[1];
		m_targetJointAngle_All.data[10] = m_targetJointAngle_Leg.data[2];
	}

	m_targetJointAngle_AllOut.write();

	
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t CollectJointAngle::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CollectJointAngle::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CollectJointAngle::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CollectJointAngle::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t CollectJointAngle::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void CollectJointAngleInit(RTC::Manager* manager)
  {
    coil::Properties profile(collectjointangle_spec);
    manager->registerFactory(profile,
                             RTC::Create<CollectJointAngle>,
                             RTC::Delete<CollectJointAngle>);
  }
  
};


