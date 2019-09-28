/*
    Technical Project Specific Essential Function Header File by Janrey "CodexLink" Licas
    File Category Type: Core Function Definitions, "CoreDef".
*/

/*

Things To Know #1 - ENUMs,
	A Group or contains that specific values that classifies specialized for returning
	reference values. For example, we need a group of reference values for returning error codes.
	Hence, this example is refernced to our first ENUM called TERM_RET_ERROR
*/

#ifndef TechProSpEssential_TTRM_H
#define TechProSpEssential_TTRM_H // We define this marker for indication of "already initialized"

#include <iostream>
#include <conio.h>
#include <string>
#include <deque>
#include <stack>
#include <windows.h> // For Win32 API, We manipulate our console here.
#include "WinToastLib/wintoastlib.h"
#include "SQLite3/sqlite3.h"
//#include <conio.h> // For Character Standard Input (STDIN) Capture for Switch-Case Statement
#include <chrono>
#include <thread>
#include <limits>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <iomanip>

// #define Function-Like Declaration and Constant Uncategorized Definitions
#define PROJECT_NAME L"Quick Task To Me C++ CLI"
#define PROJECT_VER L"Early Testing Case"
#define delay_time(x) std::this_thread::sleep_for(std::chrono::milliseconds(x))
#define WinCall_CMD(x) system(x);
#define CinBuffer_ClearOptpt(__CharIgnore_Start) std::cin.ignore(std::numeric_limits<std::streamsize>::max(), __CharIgnore_Start);
using namespace WinToastLib;

#undef max // Visual Studio Overriding Function To Be Undefined.

// ! Regarding 'This' Pragma. The reason of declaring this one is because of an issue about arguments that can be passed both on localtime_s and mktime. localtime_s needs a struct tm while mktime needs a struct *tm. This issue was caused on code issue where allocation happens and possible memory leak might be the result which is a bad idea.

#pragma warning(disable : 4996) //_CRT_SECURE_NO_WARNINGS

// TERM_RET_ERROR - An ENUM that contains Termination Return Error. Useful for Deconstructor Error Display
/* CODE_RET_PROCESS
	Contents: Function Returning Values for Processing Functions
	Reason for ENUM to #define: 
*/
#ifndef CODE_RET_PROCESS
#define CODE_RET_PROCESS
#define RETURN_NULL 0
#define USER_OUTOFSCOPE_TERM_SUCCESS 0
#endif

/* CODE_CONSTANTS is using Define not ENUM.
	Technical Reason: Not Usable as an Incrementable Reference.
*/
#ifndef CODE_CONSTANTS
#define CODE_CONSTANTS
#define INIT_NULL_INT 0
#define INIT_BY_LITERAL_ONE 1
#define INIT_NULL_STR ""
#define INIT_NULL_CHAR '0'
#define POS_OFFSET_BY_ONE 1
#define BY_ONE_OR_LESS 1
#define DO_NOTHING 0

// Superposition Method, Parameters used for when we want to run this function content or not. Used for Selected Technical  Functions only.
#define IGNORE_PROCESS 0
#define RUN_PROCESS 1
#define NOT_REQ_TERM 1
#define PROCESS_AWAIT_CMPLT 1 // Awaiting Completion
#endif

// SYS_CONSTRAINTS is a set of definition for parameter constraints designed for stopping operation when user execeeded to one of the range definitions declared below.
#ifndef SYS_CONSTRAINTS
#define SYS_CONSTRAINTS
#define MIN_CHAR_TASKNAME 2
#define MIN_CHAR_INCHARGE 2
#define MIN_TIME_DAY 1
#define MAX_TIME_DAY 31
#define MIN_TIME_MONTH 1
#define MAX_TIME_MONTH 12
#define MIN_TIME_HOUR 0
#define MAX_TIME_HOUR 23
#define MIN_TIME_MIN 0
#define MAX_TIME_MIN 59
#define MIN_TIMELEFT 0
#define MAX_TIMELEFT 180

#define TASK_DISPLAY_LIMIT 5
#define TASK_DISPLAY_CRUD 10
#define MAX_TASK_ATTACHABLE 50
#define MAX_TASK_DATABASE 50
#define START_CTIME 1900
#define MAX_SIZE ...
#endif

/*
    TTRM is base class that initializes...
*/
class TTRM
{
	/*
		This class class contain variables, objects structors and functions.
		So here's na overview.
		- Constructors
		- Variables
		- Structs
		- Enums
		- Functions
	*/
public:
	typedef enum
	{
		WinToastID = 10,
		AutoStartID = 11,
		SQLiteID = 12
	} ComponentID; // This enum is only used for identifying Components To Check.

	enum TERM_RET_ERROR : unsigned short
	{
		TERM_SUCCESS,
		TERM_FAILED,
		TERM_INVALID_PARAM
	};

	enum SQLite_QueryType
	{
		AddData,
		EditData,
		DeleteData
	};

	enum REMINDER_TYPES : unsigned int
	{
		CancelOperation,
		QuickRemind,
		DateBasedRemind,
	};

	enum SET_CHOICE_PROCESS : char
	{
		CONFIRMED_TRUE_LOWER = 'y',
		CONFIRMED_TRUE_UPPER = 'Y',
		CONFIRMED_FALSE_LOWER = 'n',
		CONFIRMED_FALSE_UPPER = 'N'

	};

	enum TERM_CONSOLE_LOG_PRESET
	{
		//
	};

	// CODE_CONSTRAINT_DEFAULT - An ENUM that contains Constraint to any function.
	enum CODE_CONSTRAINT_DEFAULT
	{
		LIMIT_ARGC_COUNTER = 5,
		MAX_TASK_EXISTING = 255 // Used for limiting possible task to enter.
	};

	enum DISPLAY_OPTIONS
	{
		Termination,
		AddTask,
		DeleteTask,
		EditTask,
		ViewTask,
		SortTask,
		RemoveAllTask,
		AtHome
	};

	enum SLEEP_TIMERS
	{
		SLEEP_INIT_SETUP = 2000,
		SLEEP_DISPLAY_WINDOW = 1500,
		SLEEP_INIT_OBJECT = 2000,
		SLEEP_TERM = 3000,
		SLEEP_ERROR_PROMPT = 1850,
		SLEEP_SIGNIFICANT_ERR = 3000,
		SLEEP_OPRT_FAILED = 2500,
		SLEEP_OPRT_FINISHED = 1500
	};

	TTRM(void)
	{
		std::cout << "Quick Tasks To Remind Me C++ CLI, Version 09/28/2019-2026" << std::endl
				  << std::endl
				  << "Created by Data Structure Group 5, Group Members {\nProject Leader and Program Developer: 'Janrey Licas',\n AppFlow Director: 'Rejay Mar'\n};" << std::endl
				  << std::endl;
		delay_time(SLEEP_INIT_OBJECT);
	}

	~TTRM(void)
	{
		std::cout << "Termination |> Closing Objects and Database before closing the program." << std::endl;
		std::cout << "Termination |> All Modules Is Closed. Program Terminates!" << std::endl;
		delay_time(SLEEP_INIT_OBJECT);
		exit(USER_OUTOFSCOPE_TERM_SUCCESS);
	}

	// TTRM's CoreFunc Functions
	void ParseGivenParam(unsigned short argcount, char *argcmd[]);
	virtual unsigned short ComponentCheck(bool isNeededToRun) noexcept(false);

	void runSystemMenu() noexcept(false);
	std::string DisplayItem_ParseType(REMINDER_TYPES IntType) noexcept;
	void DisplayTasks_AtWindow(DISPLAY_OPTIONS WindowID_INT) noexcept;
	// TTRM_WinToast Relative Functions. Not Decalred to TTRM_WinToast due to Function Structure of the whole class.

	void WinToast_RemindTask() noexcept;
	void WinToast_ShowTaskCForToday() noexcept;
	void WinToast_ShowReminder() noexcept;
	std::string runSystem_GetTimeLocal() const noexcept;
	// Status Indicator Checkers
	std::string ComponentStats_Indicator(ComponentID CompToCheck) noexcept;
	void MenuSel_ATask() noexcept(false);
	void MenuSel_DTask() noexcept;
	void MenuSel_ETask() noexcept(false);
	void MenuSel_VTask() noexcept(false);
	void MenuSel_SQT() noexcept(false); // SortQueuedTask
	void MenuSel_RQT() noexcept(false); // RemoveQueuedTask
	// TTRM's TechFunc Functions
	void SQLite_Initialize() const noexcept(false); // CreateTable Must Be Here
	void SQLite_CheckDatabase() const noexcept(false);
	void SQLite_ReloadQueue() const noexcept(false);
	void SQLite_CRUD_Data(SQLite_QueryType ExecutionQueryType) const noexcept(false);
	// These variables will be globally use by functions to reduce variable initialization by candidating only few ones from the class state.
	unsigned short TASK_LIMIT_SIZE = TASK_DISPLAY_LIMIT; // By Default, 5.
	char handleInputChar = INIT_NULL_CHAR;
	unsigned short handleInputInt = INIT_NULL_INT;
	unsigned short IterHandler_UnSh = INIT_NULL_INT;
	unsigned int IterHandler_UnIn = INIT_NULL_INT;
	signed int IterHandler_SiIn = INIT_NULL_INT;
	signed short IterHandler_SiSh = INIT_NULL_INT;

protected:
	const std::string DB_Path = "SQL_DataTest.db"; // Unconfirmed
};

/*
	TTRM_WinToast is a base class specifically seperated to use WinToast Class 'IWinToastHandler'
	We seperated this for a reason. The reason why is because according to the template or the 
	same code, we have to call 'this' (TTRM_WinToast) class everytime we are gonna display some toast.
	IF we didn't seperate this class from one another, we cannot initiate it.
*/
class TTRM_WinToast : public IWinToastHandler
{
public:
	TTRM_WinToast(void) {}
	~TTRM_WinToast(void)
	{
		WinToast::instance()->clear();
	}
	void toastActivated() const
	{
		;
		//	std::wcout << L"The user clicked in this toast" << std::endl;
		//	exit(0);
	}
	void toastActivated(int actionIndex) const
	{
		;
		//	std::wcout << L"The user clicked on action #" << actionIndex << //std::endl;
		//	exit(16 + actionIndex);
	}
	void toastDismissed(WinToastDismissalReason state) const
	{
		switch (state)
		{
		case UserCanceled:
			//		std::wcout << L"The user dismissed this toast" << std::endl;
			//		exit(1);
			break;
			//	case TimedOut:
			//		std::wcout << L"The toast has timed out" << std::endl;
			//		exit(2);
			//		break;
		case ApplicationHidden:
			//		std::wcout << L"The application hid the toast using //ToastNotifier.hide()" << std::endl;
			//		exit(3);
			break;
		default:
			//		std::wcout << L"Toast not activated" << std::endl;
			//		exit(4);
			break;
		}
	}
	void toastFailed() const
	{
		;
		//	std::wcout << L"Error showing current toast" << std::endl;
		//	exit(5);
	}
};

/*
 TTRM_TaskData is an important base class that utilizes System-Proposed Functions specificially used for scheduler. This means that all functions residing
 in this class is basically related to the Proposed System that we wanted to make. This base class was not on a confirmed status. Please be advised.
*/
class TTRM_TaskData
{

public:
	std::string TaskName = INIT_NULL_STR;
	std::string TaskInCharge = INIT_NULL_STR;
	unsigned short ReminderType = INIT_NULL_INT;
	signed short NotifyByTime = INIT_NULL_INT;
	tm *TempTM = {0};
	tm RemindTime = {0};
	tm TargetDateTime = {0}; // Used for REMINDER_TYPES::DateBasedRemind and Quick Time
};
#endif