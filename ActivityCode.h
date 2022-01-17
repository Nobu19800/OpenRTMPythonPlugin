/*!
 * @file  ActivityCode.h
 * @brief アクティビティの定義
 *
 */

#ifndef ACTIVITYCODE_H
#define ACTIVITYCODE_H

#include <QString>

namespace rtmiddleware {
	/**
	 * @enum ActivityCode
	 * @brief アクティビティ一覧
	 */
	enum ActivityCode
	{
		code_onInitialize = 0,
		code_onFinalize = 1,
		code_onStartup = 2,
		code_onShutdown = 3,
		code_onActivated = 4,
		code_onDeactivated = 5,
		code_onExecute = 6,
		code_onAborting = 7,
		code_onError = 8,
		code_onReset = 9,
		code_onStateUpdate = 10,
		code_onRateChanged = 11,
		code_inputFromSimulator = 12,
		code_outputToSimulator = 13,
		code_setBody = 14,
		code_num = 15
	};

	/**
	 * @fn
	 * @brief アクティビティのIDを文字列に変換する
	 * @param id アクティビティのID
	 * @return 文字列
	 */
	QString Activity_toString(ActivityCode id);

}
#endif // ACTIVITYCODE_H
