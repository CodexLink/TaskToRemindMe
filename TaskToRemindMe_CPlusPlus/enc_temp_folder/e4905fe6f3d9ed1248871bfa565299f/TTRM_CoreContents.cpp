/*
    Technical Project Specific Essential Function CPP File by Janrey "CodexLink" Licas
    File Category Type: Technical and Core Function Body Definition, "CoreFunc".
	
	Overview	 

	- Core Functions

	- Technical Functions
*/

#include "TTRM_CoreDeclares.h"

std::deque<TTRM_TaskData> TaskList;

void TTRM::ParseGivenParam(unsigned short argcount, char *argv[])
{
	unsigned int ParamIter = INIT_NULL_INT;
	std::cout << "Quick Tasks To Remind Me C++ in CLI version. BETA" << std::endl
			  << std::endl;
	std::cout << "Created by Data Structure Group 5, Group Members {\n Header Core Developer: 'Janrey Licas',\n AppFlow Director: 'Rejay Mar'\n};" << std::endl
			  << std::endl;
	std::cout << "[Perform Parameter Given] |> Counted Parameter: " << argcount << std::endl;
	while (!strcmp(argv[ParamIter], "") && ParamIter != LIMIT_ARGC_COUNTER)
	{
		// Create more features here. Use switch for Selection of Data here.
		std::cout << " Parameter Index " << ParamIter << " |> Parameter Value -> " << argv[ParamIter] << std::endl;
	}
}

unsigned short TTRM::ComponentCheck(bool isNeededToRun) noexcept(false)
{
	TTRM_TaskData SaveStateContainer;
	long posx = INIT_NULL_INT, posy = INIT_NULL_INT;
	try
	{
		HWND console = GetConsoleWindow(); //, hwnd = GetConsoleWindow();
		RECT ConsoleWindow, ClietnScrWindow;
		HMENU hmenu = GetSystemMenu(console, FALSE);
		SetConsoleTitle("Quick Tasks To Remind Me | C++ | Early BETA // github.com/CodexLink");
		GetClientRect(console, &ConsoleWindow);
		GetWindowRect(console, &ClietnScrWindow);
		posx = GetSystemMetrics(SM_CXSCREEN) / 2 - (ClietnScrWindow.right - ClietnScrWindow.left) / 2,
		posy = GetSystemMetrics(SM_CYSCREEN) / 2 - (ClietnScrWindow.bottom - ClietnScrWindow.top) / 2,
		MoveWindow(console, posx, posy, ClietnScrWindow.right - ClietnScrWindow.left, (ClietnScrWindow.bottom - ClietnScrWindow.top) * 1.3, TRUE);
		//MoveWindow(console, ConsoleMainApp.left, ConsoleMainApp.top, 1000, 500, TRUE);

		EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);

		std::cout << "Component Checking Point | Before Program Initialization..." << std::endl
				  << std::endl
				  << "WinToast Library |> Checking Compatibility...";
		if (WinToast::isCompatible())
		{
			std::cout << std::endl
					  << "WinToast Library |> Compatible. Setting Up Parameters..." << std::endl;
			WinToast::instance()->setAppName(L"Quick Tasks To Remind Me C++ CLI");
			WinToast::instance()->setAppUserModelId(WinToast::configureAUMI(L"Data Struct Group 5", L"Quick Tasks To Remind Me", L"QTRM C++", L"Early Beta Stage"));
			std::cout << "WinToast Library |> Application Name Loaded." << std::endl;

			WinToastTemplate WinToastInit_Welcome(WinToastTemplate::Text02);
			WinToastInit_Welcome.setTextField(PROJECT_NAME, WinToastTemplate::FirstLine);
			WinToastInit_Welcome.setTextField(L"Hello There! Program Initialized.", WinToastTemplate::SecondLine);
			WinToastInit_Welcome.setAudioPath(WinToastTemplate::Reminder);
			WinToastInit_Welcome.setAttributionText(PROJECT_NAME);
			std::cout << "WinToast Library |> Application Profile, Header and App Name Loaded." << std::endl;

			if (WinToast::instance()->initialize())
			{
				std::cout << "WinToast Library |> Initialized." << std::endl;
				if (!WinToast::instance()->showToast(WinToastInit_Welcome, new TTRM_WinToast))
				{
					std::cerr << "WinToast Library |> Error. Could Not Launch Toast Notification!" << std::endl;
					Sleep(SLEEP_SIGNIFICANT_ERR);
				}
				else
				{
					std::cout << "Save State Load  |> Opening SaveState File..." << std::endl;
					SaveStateHandler.open(SaveStatePath, std::ios::in);
					if (SaveStateHandler.is_open())
					{
						std::cout << "Save State Load  |> SaveState File Opened! Iterating and Collecting Saved Reminders";
						while (std::getline(SaveStateHandler, DataLineHandler))
						{
							std::cout << ".";
							PayloadHandler.clear();
							std::stringstream RowHandler(DataLineHandler);

							while (std::getline(RowHandler, ConvertedHandler, ','))
							{
								PayloadHandler.push_back(ConvertedHandler);
							}
							SaveStateContainer.TaskName = PayloadHandler[0];
							SaveStateContainer.TaskInCharge = PayloadHandler[1];
							SaveStateContainer.ReminderType = std::stoi(PayloadHandler[2]);
							EpochHandler = std::stoll(PayloadHandler[3]);
							SaveStateContainer.TempTM = localtime(&EpochHandler);
							SaveStateContainer.ReminderData = *SaveStateContainer.TempTM;
							++IterHandler_UnIn;
							TaskList.push_back(SaveStateContainer);
						}
						SaveStateHandler.close();
						std::cout << std::endl
								  << std::endl
								  << "Save State Loaded |> Done. Loaded " << IterHandler_UnIn << " Reminders!" << std::endl;
						IterHandler_UnIn = INIT_NULL_INT;
						std::cout << std::endl
								  << "Multi-Threading | Starting Simultaneous Wrapper..." << std::endl;
						_beginthreadex(0, 0, &TTRM::MultiThread_Wrapper, 0, 0, &MultiThreadID);
						std::cout << "Multi-Threading | Simultaneous Wrapper Initialized...";
					}
					else
					{
						std::cout << "Save State Create |> Save File Doesn't Exist. Creating Save File..." << std::endl;
						TempSaveStateHandler.open(FilePointState, std::ios::out);
						if (TempSaveStateHandler.is_open())
						{
							std::cout << "Save State Create |> SaveState File Created!" << std::endl;
							TempSaveStateHandler.close();
							rename(FilePointState, SaveStatePath);
							//remove(FilePointState);
						}
						else
						{
							std::cout << "Save State Create |> SaveState File Creation Failure. Fatal Error | Terminating Program" << std::endl;
							TTRM::~TTRM();
						}
					}
					SaveStateHandler.close();
					delay_time(SLEEP_OPRT_FINISHED);
				}
			}
			else
			{
				std::cerr << "WinToast Library |> Error. Cannot Initialize WinToast, Notification Disabled." << std::endl;
				delay_time(SLEEP_ERROR_PROMPT);
			}

			if (isNeededToRun)
			{
				return TERM_SUCCESS;
			}
			else
			{
				return TERM_FAILED;
			}
		}
		else
		{
			std::cout << std::endl
					  << "WinToast Library |> This library is not Compatible. Terminating Program...";
			return TERM_FAILED;
		}
	}
	catch (const std::runtime_error &ErrMsg)
	{
		std::cerr << "Runtime Error |> " << ErrMsg.what() << std::endl;
	}
	catch (const std::exception &ErrMsg)
	{
		std::cerr << "Exception |> " << ErrMsg.what() << std::endl;
	}
}

void TTRM::runSystemMenu() noexcept(false)
{
	unsigned int DisplayMenu_Input = INIT_NULL_INT;
	WinToast_ShowTaskCForToday();
	while (NOT_REQ_TERM)
	{
		WinCall_CMD("CLS");
		std::cout << std::endl
				  << "Quick Tasks To Remind Me C++ in CLI version. BETA" << std::endl
				  << std::endl;
		// Create function for String To Time here.

		std::cout << "Last Time Frame From Your Local System |> " << runSystem_GetTimeLocal() << std::endl;
		std::cout << std::endl
				  << "=== List of Task/s, Arranged by Recent Insertion ========" << std::endl;
		DisplayTasks_AtWindow(AtHome);
		std::cout << std::endl
				  << "=== Basic Tasks Functions ======================================" << std::endl
				  << std::endl
				  << "1 |> Add a Task" << std::endl
				  << "2 |> Delete a Task/s" << std::endl
				  << "3 |> Edit / Modify an Existing Task/s" << std::endl
				  << "4 |> View All Tasks" << std::endl
				  << "5 |> Remove All Tasks" << std::endl
				  << "6 |> Refresh Tasks from Save State" << std::endl
				  << std::endl
				  << "0 |> Terminate / Exit Program" << std::endl
				  << std::endl;

		std::cout << "[Input] Your Choice and ENTER |> ";
		std::cin >> DisplayMenu_Input;
		CinBuffer_ClearOptpt('\n');
		if (std::cin.fail())
		{
			std::cin.clear();
			CinBuffer_ClearOptpt('\n');
			std::cout << "[ERROR] User Input Error -> Input Is Non-Existing or Non-Integer." << std::endl;
			delay_time(SLEEP_ERROR_PROMPT);
			continue;
		}
		// Stack the function.
		// Return to 'this' function so that we can go back to this function easily.
		switch (DisplayMenu_Input)
		{
		case AddTask:
			MenuSel_ATask();
			break;

		case DeleteTask:
			MenuSel_DTask();
			break;

		case EditTask:
			MenuSel_ETask();
			break;

		case ViewTask:
			MenuSel_VTask();
			break;

		case RemoveAllTask:
			MenuSel_RQT();
			break;

		case Termination:
			break;

		default:
			std::cout << std::endl
					  << "[ERROR] User Inputted Not Included in the List!" << std::endl;
			delay_time(SLEEP_ERROR_PROMPT);
			break;
		}
		if (!DisplayMenu_Input)
			break;
	}
	return;
}

std::string TTRM::DisplayItem_ParseType(REMINDER_TYPES IntType) noexcept
{
	switch (IntType)
	{
	case CancelOperation:
		return "ERROR";
		break;
	case QuickRemind:
		return "Quick Reminder";
		break;
	case DateBasedRemind:
		return "Date Based Reminder";
		break;
	default:
		return "ERROR";
	}
}

void TTRM::DisplayTasks_AtWindow(DISPLAY_OPTIONS WindowID_INT) noexcept
{
	unsigned short TaskNum = INIT_BY_LITERAL_ONE, TASK_LIMIT_ITER = INIT_NULL_INT;
	bool isAtHome = false;
	if (!TaskList.size())
	{
		std::cerr << std::endl
				  << "There are no tasks in queue! Please add one." << std::endl;
		return;
	}
	else
	{
		std::cout << std::endl
				  << "There" << (TaskList.size() <= BY_ONE_OR_LESS ? " is " : " are ") << TaskList.size() << (TaskList.size() <= BY_ONE_OR_LESS ? " task" : " tasks");
		switch (WindowID_INT)
		{
		case DeleteTask:
			std::cout << " available to delete!" << std::endl
					  << std::endl;
			break;
		case EditTask:
			std::cout << " available to edit!" << std::endl
					  << std::endl;
			break;
		case ViewTask:
			std::cout << " in total at queue system!" << std::endl
					  << std::endl;
			break;

		case RemoveAllTask:
			std::cout << " removed from the system!" << std::endl;
			break;

		case AtHome:
			isAtHome = true;
			std::cout << " for today~!" << std::endl
					  << std::endl;
			break;
		default:
			std::cerr << "... ???" << std::endl;
		}
		// ! This function is degrading grade of code quality due to completixty. Try to do some method to reduce this.
		// TODO: Normalize This Function.
		for (auto IterTasks : TaskList)
		{
			if (isAtHome && TaskNum > TASK_LIMIT_SIZE)
			{
				std::cout << std::endl
						  << "And there are other " << (TaskList.size() + POS_OFFSET_BY_ONE) - TaskNum << (((TaskList.size() + POS_OFFSET_BY_ONE) - TaskNum) == BY_ONE_OR_LESS ? " task" : " tasks") << " available!" << std::endl;
				break;
			}
			else
			{
				std::cout << "Task # " << TaskNum << " | ";

				switch (IterTasks.ReminderType)
				{
				case QuickRemind:
					// ! Done
					std::cout << DisplayItem_ParseType((TTRM::REMINDER_TYPES)IterTasks.ReminderType) << " |> " << IterTasks.TaskName << " | In Charge: " << IterTasks.TaskInCharge << ", Trigger Time at " << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_hour << ":" << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_min << std::endl;
					break;

				case DateBasedRemind:
					// ! Done
					std::cout << DisplayItem_ParseType((TTRM::REMINDER_TYPES)IterTasks.ReminderType) << " |> " << IterTasks.TaskName << " | In Charge |> " << IterTasks.TaskInCharge << ", Date and Time Trigger |> " << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_mon + 1 << "/" << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_mday << "/" << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_year + START_CTIME << ", " << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_hour << ":" << std::setfill('0') << std::setw(2) << IterTasks.ReminderData.tm_min << std::endl;
					break;

				default:
					break;
				}
				TaskNum++;
			}
		}
		return;
	}
}

std::string TTRM::runSystem_GetTimeLocal() const noexcept
{
	tm TimeStorage;
	time_t TimeStamp = time(NULL);
	std::stringstream StrTime;
	localtime_s(&TimeStorage, &TimeStamp);
	StrTime << TimeStorage.tm_mon + POS_OFFSET_BY_ONE << "/" << std::setfill('0') << std::setw(2) << TimeStorage.tm_mday << "/" << std::setfill('0') << std::setw(2) << (TimeStorage.tm_year + START_CTIME) << " | " << std::setfill('0') << std::setw(2) << TimeStorage.tm_hour << ":" << std::setfill('0') << std::setw(2) << TimeStorage.tm_min << ":" << std::setfill('0') << std::setw(2) << TimeStorage.tm_sec;
	return StrTime.str();
}

void TTRM::WinToast_ShowTaskCForToday() noexcept
{
	WinToast::instance()->clear(); // Clears First Toast. Overwritten by 'this' template.
	WinToastTemplate TaskCountShow(WinToastTemplate::Text02);
	std::wstring TaskCount = std::to_wstring(TaskList.size());
	std::wstring WelcomeFirstPT = L"Hello User! You currently have ";
	std::wstring WelcomeSecondPT = (TaskList.size() <= BY_ONE_OR_LESS) ? L" task" : L" tasks";
	std::wstring WelcomeThirdPT = L" for today.";

	TaskCountShow.setTextField(PROJECT_NAME, WinToastTemplate::FirstLine);
	TaskCountShow.setAttributionText(L"Data Struct Group 5");
	TaskCountShow.setTextField(WelcomeFirstPT + TaskCount + WelcomeSecondPT + WelcomeThirdPT, WinToastTemplate::SecondLine);
	// We dont check anything, since we have done it in the first place.
	WinToast::instance()->showToast(TaskCountShow, new TTRM_WinToast);
	return;
}

void TTRM::WinToast_ReminderPrompt(std::string ReadTaskName, std::string ReadPersonInCharge, unsigned short ReadReminderType, signed ReadNotifyByTime, tm TMToRead) noexcept
{
	// * WString Conversion from std::String. We don't want to change things globally by replacing std::string with std::wstring. Too late to change something that most functions used.
	std::wstring ConvWStr_TaskN(ReadTaskName.begin(), ReadTaskName.end());
	std::wstring ConvWStr_RPIC(ReadPersonInCharge.begin(), ReadPersonInCharge.end());

	std::wstringstream ConvWStr_DateTimeData;

	// ! Wstring Constant, We cannot concatenate literal strings with variables. We can only concatenate with variable to variable with + operator.

	WinToast::instance()->clear();
	WinToastTemplate ShowReminder(WinToastTemplate::Text04);

	if (ReadReminderType == QuickRemind)
	{
		ConvWStr_DateTimeData << L"Time Triggered at " << std::setw(2) << std::setfill(L'0') << TMToRead.tm_hour << L":" << std::setw(2) << std::setfill(L'0') << TMToRead.tm_min;
		ShowReminder.setTextField(L"Quick Reminder Triggered~!", WinToastTemplate::FirstLine);
		ShowReminder.setTextField(ConvWStr_DateTimeData.str(), WinToastTemplate::ThirdLine);
	}
	else
	{
		ConvWStr_DateTimeData << L"Date Time Triggered at " << std::setfill(L'0') << std::setw(2) << (TMToRead.tm_mon + 1) << "/" << std::setfill(L'0') << std::setw(2) << TMToRead.tm_mday << "/" << std::setfill(L'0') << std::setw(2) << (TMToRead.tm_year + START_CTIME) << ", " << std::setfill(L'0') << std::setw(2) << TMToRead.tm_hour << ":" << std::setfill(L'0') << std::setw(2) << TMToRead.tm_min << std::endl;
		ShowReminder.setTextField(L"Date-Based Reminder Triggered~!", WinToastTemplate::FirstLine);
		ShowReminder.setTextField(ConvWStr_DateTimeData.str(), WinToastTemplate::ThirdLine);
	}
	ShowReminder.setTextField(L"Task " + ConvWStr_TaskN + L" for " + ConvWStr_RPIC, WinToastTemplate::SecondLine);

	ShowReminder.setAttributionText(PROJECT_NAME);
	ShowReminder.setDuration(WinToastTemplate::Duration::Long);

	// Snooze will have it only 15 minutes.
	ShowReminder.addAction(L"Snooze for 15 Minutes");
	ShowReminder.addAction(L"Dismiss");

	ShowReminder.setAudioPath(WinToastTemplate::Reminder);
	WinToast::instance()->showToast(ShowReminder, new TTRM_WinToast);
}

unsigned int __stdcall TTRM::MultiThread_Wrapper(void *DataReserved)
{
	HANDLE MultiThreadWrapper;
	while (1)
	{
		MultiThreadWrapper = (HANDLE)_beginthreadex(0, 0, &TTRM::MultiThread_ScanReminders, 0, 0, 0);
		WaitForSingleObject(MultiThreadWrapper, INFINITE);
		delay_time(WAIT_STARTTHREAD);
	}
	return USER_OUTOFSCOPE_TERM_SUCCESS;
}

// This function should be scanning 10 reminders at ones.
unsigned int __stdcall TTRM::MultiThread_ScanReminders(void *ArgsReserved)
{
	auto ObjectScanIter = INIT_NULL_INT;
	time_t ObjSlotScanConv = INIT_NULL_INT;
	if (TaskList.size())
	{
		//std::cout << ".";
		//std::cout << mktime(&TaskList.at(ObjectScanIter).ReminderData) << " | " << time(NULL) << std::endl;
		//WinToast_ReminderPrompt(TaskList.at(ObjectScanIter).TaskName, TaskList.at(ObjectScanIter).TaskInCharge, TaskList.at(ObjectScanIter).ReminderType, TaskList.at(ObjectScanIter).NotifyByTime, TaskList.at(ObjectScanIter).ReminderData);
		for (ObjectScanIter = INIT_NULL_INT; ObjectScanIter < TaskList.size(); ObjectScanIter++)
		{
			if (mktime(&TaskList.at(ObjectScanIter).ReminderData) <= time(NULL))
			{
				WinToast_ReminderPrompt(TaskList.at(ObjectScanIter).TaskName, TaskList.at(ObjectScanIter).TaskInCharge, TaskList.at(ObjectScanIter).ReminderType, TaskList.at(ObjectScanIter).NotifyByTime, TaskList.at(ObjectScanIter).ReminderData);
				while (1)
				{
					//delay_time(10000);
				}
			}
		}
	}
	else
	{
		return NO_TASK_REPEAT_PRC; // We wont exit this scope anyway unless we call destructor...
	}
}

void TTRM::MenuSel_ATask() noexcept(false)
{
	time_t CompareUserDate = INIT_NULL_INT, CompareStoredDate = INIT_NULL_INT;
	short int ObjIterateNum = INIT_NULL_INT;
	double diffDateHandler = INIT_NULL_INT;
	while (PROCESS_AWAIT_CMPLT)
	{
		TTRM_TaskData NewTask; // Create Object To Pass On...
		time_t CurrentDateTime = time(NULL);
		tm *CurrentTContainer = localtime(&CurrentDateTime);
		WinCall_CMD("CLS");

		std::cout << "[Required] Name of the Task, Input --CANCEL to Quit Insertion. |> ", std::getline(std::cin, NewTask.TaskName);

		if (NewTask.TaskName.length() < MIN_CHAR_TASKNAME || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> TaskName Character Is Not Enough. Press Enter Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			continue;
		}
		else if (NewTask.TaskName == "--CANCEL")
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> New Task Insertion Operation is Cancelled by User..." << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			return;
		}

		std::cout << "[Required] Name of Person In Charge, Input --CANCEL to Quit Insertion. |> ", std::getline(std::cin, NewTask.TaskInCharge);

		if (NewTask.TaskInCharge.length() < MIN_CHAR_INCHARGE || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> Task In Charge Character Is Not Enough. Press Enter Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			continue;
		}
		else if (NewTask.TaskInCharge == "--CANCEL")
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> New Task Insertion Operation is Cancelled by User..." << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			return;
		}

		std::cout << "[Req, 0 = To Cancel, 1 = Quick Remind, 2 = Date-Based]"
				  << " |> Type of Reminder |> ",
			std::cin >> NewTask.ReminderType;

		if (NewTask.ReminderType < CancelOperation || NewTask.ReminderType > DateBasedRemind || std::cin.fail())
		{
			std::cin.clear();
			std::cerr << "[INPUT ERR] |> Reminder Type Input is Invalid. Press Any Key To Try Again." << std::endl;
			CinBuffer_ClearOptpt('\n');
			_getche();
			continue;
		}
		else
		{
			switch (NewTask.ReminderType)
			{
			case CancelOperation:
				std::cerr << "[INPUT ERR] |> New Task Insertion Operation is Cancelled by User..." << std::endl;
				delay_time(SLEEP_OPRT_FINISHED);
				return;

			case QuickRemind:
				std::cout << "[Required, Min: 1, Max: 180] Minutes Left To Remind You |> ", std::cin >> NewTask.NotifyByTime;
				if (NewTask.NotifyByTime <= MIN_TIMELEFT || NewTask.NotifyByTime > MAX_TIMELEFT)
				{
					std::cerr << "[INPUT ERR] |> Time Entered is invalid. Please try again by pressing any key to restart." << std::endl;
					CinBuffer_ClearOptpt('\n');
					_getche();
					continue;
				}
				else
				{
					// * Test Done. Success.
					CurrentDateTime = time(NULL) + (60 * NewTask.NotifyByTime);
					NewTask.TempTM = localtime(&CurrentDateTime);
					NewTask.ReminderData = *NewTask.TempTM;
					break;
				}

			case DateBasedRemind:
				CurrentDateTime = time(NULL);
				NewTask.TempTM = localtime(&CurrentDateTime);
				NewTask.ReminderData = *NewTask.TempTM;

				std::cout << "[Req, Seperate by Space | MM DD YYYY] Target Date of Reminding |> ", NewTask.ReminderData.tm_mon >> NewTask.ReminderData.tm_mday >> NewTask.ReminderData.tm_year;

				if (NewTask.ReminderData.tm_year < CurrentTContainer->tm_year)
				{
					std::cin.clear();
					std::cerr << "[INPUT ERR] |> Target Year Parameter is either invalid or less from current date. Press Any Key To Try Again." << std::endl;
					CinBuffer_ClearOptpt('\n');
					_getche();
					continue;
				}
				else
				{
					if (NewTask.ReminderData.tm_mon < MIN_TIME_MONTH || NewTask.ReminderData.tm_mon > MAX_TIME_MONTH || NewTask.ReminderData.tm_mon < CurrentTContainer->tm_mon || std::cin.fail())
					{
						std::cin.clear();
						std::cerr << "[INPUT ERR] |> Target Month Parameter is either invalid or less from current date. Press Any Key To Try Again." << std::endl;
						CinBuffer_ClearOptpt('\n');
						_getche();
						continue;
					}
					else
					{
						if (NewTask.ReminderData.tm_mday < MIN_TIME_DAY || NewTask.ReminderData.tm_mday > MAX_TIME_DAY || (NewTask.ReminderData.tm_year == CurrentTContainer->tm_year && NewTask.ReminderData.tm_mon == CurrentTContainer->tm_mon && (NewTask.ReminderData.tm_mday < CurrentTContainer->tm_mday)) || std::cin.fail())
						{
							// ! If same month, check day.
							std::cin.clear();
							std::cerr << "[INPUT ERR] |> Target Day Parameter is either invalid or less from current date. Press Any Key To TryAgain." << std::endl;
							CinBuffer_ClearOptpt('\n');
							_getche();
							continue;
						}
					}
					std::cout << "[Req, Seperate by Space | 00:00 - 23:59] Time To Remind You |> ", std::cin >> NewTask.ReminderData.tm_hour >> NewTask.ReminderData.tm_min;

					// ! Add Some Today To Today Sens Time. Currently WORK ON PROGRESS.
					if ((NewTask.ReminderData.tm_hour > MIN_TIME_HOUR || NewTask.ReminderData.tm_hour <= MAX_TIME_HOUR) || (NewTask.ReminderData.tm_min >= MIN_TIME_MIN || NewTask.ReminderData.tm_min <= MAX_TIME_MIN) || !std::cin.fail())
					{

						// ! Prerequisite Condition, we can only get to this point if and only the datetime is exactly the same as the user added. Means 09/24/2019 == 09/24/2019. If we intend to have same date but different year then we go to else statement.

						if (NewTask.ReminderData.tm_year == CurrentTContainer->tm_year && (NewTask.ReminderData.tm_mon == CurrentTContainer->tm_mon && NewTask.ReminderData.tm_mday == CurrentTContainer->tm_mday))
						{

							// ! Prerequisite Condition, if the datetime is exactly the same as the user added. Means 09/24/2019 == 09/24/2019. We check if the latest time is added by the user greater or less than.
							// * Exactly done conditioning.

							if (NewTask.ReminderData.tm_hour >= CurrentTContainer->tm_hour)
							{
								if (NewTask.ReminderData.tm_min < CurrentTContainer->tm_min)
								{
									std::cerr << "[INPUT ERR] |> Time Minute is Less Than the Expected Day. Please Try Again." << std::endl;
									CinBuffer_ClearOptpt('\n');
									_getche();
									continue;
								}
								else
								{
									break;
								}
							}
							else
							{
								std::cerr << "[INPUT ERR] |> Time Hour is Lesser Than Expected Hour. Please Try Again." << std::endl;
								CinBuffer_ClearOptpt('\n');
								_getche();
								continue;
							}
						}
						else
						{
							// ! We proceed as there will be no conflict at timing.
							break;
						}
					}
					else
					{
						std::cin.clear();
						std::cerr << "[INPUT ERR] |> Time Input is Invalid. Keep in mind that I need 24 hour format. Press Any Key To Try Again." << std::endl;
						CinBuffer_ClearOptpt('\n');
						_getche();
						continue;
					}
					break;
				}
			default:
				std::cout << "Error" << std::endl;
				system("pause");
				continue;
			}

			try
			{
				SaveStateHandler.open(SaveStatePath, std::ios::out | std::ios::app);
				if (SaveStateHandler.is_open())
				{
					if (NewTask.ReminderType == QuickRemind)
					{
						SaveStateHandler << NewTask.TaskName << "," << NewTask.TaskInCharge << "," << NewTask.ReminderType << "," << mktime(NewTask.TempTM) << std::endl;
					}
					else
					{
						NewTask.ReminderData.tm_year -= 1900, NewTask.ReminderData.tm_mon -= 1, NewTask.ReminderData.tm_sec = 0;
						SaveStateHandler << NewTask.TaskName << "," << NewTask.TaskInCharge << "," << NewTask.ReminderType << "," << mktime(&NewTask.ReminderData) << std::endl;
					}
					TaskList.push_back(NewTask);
				}

				SaveStateHandler.close();
				std::cout << std::endl
						  << "[PROCESS] |> Task '" << NewTask.TaskName << "' has been successfully added to the queue!";
				delay_time(SLEEP_OPRT_FINISHED);
				break;
			}
			catch (std::exception &ErrMessage)
			{
				std::cerr << std::endl
						  << ErrMessage.what() << std::endl;
				delay_time(SLEEP_SIGNIFICANT_ERR);
				continue;
			}
			catch (...)
			{
				std::cerr << "[PROCESS] Unknown Error..." << std::endl;
				delay_time(SLEEP_SIGNIFICANT_ERR);
				continue;
			}
		}
	}
	return;
}
void TTRM::MenuSel_DTask() noexcept
{
	while (PROCESS_AWAIT_CMPLT)
	{
		size_t TaskSize = TaskList.size();
		WinCall_CMD("CLS");
		if (TaskSize)
		{
			std::cout << std::endl
					  << "=== Task List Available ===============================" << std::endl;
			DisplayTasks_AtWindow(DeleteTask);
			std::cout << std::endl
					  << "Please Select A Task To Delete..." << std::endl;
			std::cout << "[Input] Task # or '0' To Go Back Menu |> ", std::cin >> handleInputInt;
			if (std::cin.fail())
			{
				std::cin.clear();
				CinBuffer_ClearOptpt('\n');
				std::cerr << "[Input Error] -> Value Received is Invalid. Please try again." << std::endl;
				delay_time(SLEEP_ERROR_PROMPT);
				continue;
			}
			else
			{
				if (handleInputInt)
				{
					if (handleInputInt <= TaskSize)
					{
						std::cout << std::endl
								  << "Are you sure you want to delete this task: '" << TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName << "'?" << std::endl
								  << std::endl
								  << "[Input, Y or N] |> ",
							std::cin >> handleInputChar;
						if (std::cin.fail())
						{
							std::cin.clear();
							CinBuffer_ClearOptpt('\n');
							std::cerr << "[Input Error] -> Value Received is Invalid. Please try again." << std::endl;
						}
						else
						{
							switch (handleInputChar)
							{
							case CONFIRMED_TRUE_LOWER:
							case CONFIRMED_TRUE_UPPER:

								SaveStateHandler.open(SaveStatePath, std::ios::in);
								TempSaveStateHandler.open(FilePointState, std::ios::out);

								while (!SaveStateHandler.eof())
								{
									PayloadHandler.clear();
									std::getline(SaveStateHandler, DataLineHandler);
									std::stringstream TempDataHandler(DataLineHandler);

									for (DataLineHandler; std::getline(TempDataHandler, ConvertedHandler, ','); PayloadHandler.push_back(ConvertedHandler))
										;
									// * We delete data by comparing saved epoch task and system saved epoch task.
									if (std::stoll(PayloadHandler[3]) != mktime(&TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData))
									{
										if (!SaveStateHandler.eof())
										{
											for (IterHandler_UnSh = INIT_NULL_INT; IterHandler_UnSh < PayloadHandler.size(); IterHandler_UnSh++)
											{
												TempSaveStateHandler << PayloadHandler[IterHandler_UnSh] << (IterHandler_UnSh == (PayloadHandler.size() - POS_OFFSET_BY_ONE) ? "\n" : ",");
											}
										}
										break;
									}
									else
									{
										std::cout << std::endl
												  << std::stoll(PayloadHandler[3]) << " " << mktime(&TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData);
									}
								}
								SaveStateHandler.close();
								TempSaveStateHandler.close();

								remove(SaveStatePath);
								rename(FilePointState, SaveStatePath);

								std::cout << "[Confirmation, Success] |> Task '" << TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName << "' deleted." << std::endl;
								TaskList.erase(TaskList.begin() + (handleInputInt - POS_OFFSET_BY_ONE));
								system("pause");
								delay_time(SLEEP_OPRT_FINISHED);
								continue;

							case CONFIRMED_FALSE_LOWER:
							case CONFIRMED_FALSE_UPPER:
								std::cout << "[Confirmation, Success] |> Task Modification Cancelled." << std::endl;
								delay_time(SLEEP_OPRT_FINISHED);
								continue;

							default:
								std::cout << "[Confirmation, Error] |> User Input Invalid." << std::endl;
								std::cin.clear();
								CinBuffer_ClearOptpt('\n');
								delay_time(SLEEP_OPRT_FAILED);
								continue;
							}
						}
					}
					else
					{
						std::cerr << "[Input Error] -> User Requested To Delete Tasks Non-Existent or Out of Range..." << std::endl;
						delay_time(SLEEP_ERROR_PROMPT);
						continue;
					}
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			std::cerr << "[View Info] > Task Queue is currently empty! Please add some task/s." << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			break;
		}
	}
	return;
}
void TTRM::MenuSel_ETask() noexcept(false)
{
	while (PROCESS_AWAIT_CMPLT)
	{
		TTRM_TaskData NewModifiedTask; // Create Object To Pass On...
		time_t CurrentDateTime = time(NULL);
		tm *CurrentTContainer = localtime(&CurrentDateTime);
		size_t TaskSize = TaskList.size();
		WinCall_CMD("CLS");
		if (TaskSize)
		{
			std::cout << std::endl
					  << "=== Task Lists ===========================================" << std::endl;
			DisplayTasks_AtWindow(EditTask);
			std::cout << std::endl
					  << "[Input] Please Select A Task # or '0' To Go Back Menu |> ",
				std::cin >> handleInputInt;
			if (std::cin.fail())
			{
				std::cin.clear();
				CinBuffer_ClearOptpt('\n');
				std::cerr << "[Input Error] -> Input Invalid. Please try again." << std::endl;
				delay_time(SLEEP_ERROR_PROMPT);
				continue;
			}
			else
			{
				if (handleInputInt)
				{
					if (handleInputInt <= TaskSize)
					{
						std::cout << "[WARNING] |> Are you sure you want to edit this task: '" << TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName << "'?" << std::endl
								  << "[INPUT  ] | ['Y'es or 'N'o] |> ",
							std::cin >> handleInputChar;
						if (std::cin.fail())
						{
							std::cerr << "[Input Error] -> Value Received is Invalid. Please try again." << std::endl;
							std::cin.clear();
							CinBuffer_ClearOptpt('\n');
						}
						else
						{
							switch (handleInputChar)
							{
							case CONFIRMED_TRUE_LOWER:
							case CONFIRMED_TRUE_UPPER:
								CinBuffer_ClearOptpt('\n');
								std::cout << "[Required] Name of the Task, Put '0' To Retain Changes |> ", std::getline(std::cin, NewModifiedTask.TaskName);
								if (NewModifiedTask.TaskName != "0")
								{
									if (NewModifiedTask.TaskName.length() <= MIN_CHAR_TASKNAME || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << "[INPUT ERR] |> TaskName Character Is Not Enough. Press Enter Key To Try Again." << std::endl;
										CinBuffer_ClearOptpt('\n');
										continue;
									}
								}
								std::cout << "[Required] Name of Person In Charge, Put '0' To Retain Changes |> ", std::getline(std::cin, NewModifiedTask.TaskInCharge);
								if (NewModifiedTask.TaskInCharge != "0")
								{
									if (NewModifiedTask.TaskInCharge.length() < MIN_CHAR_INCHARGE || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << "[INPUT ERR] |> Task In Charge Character Is Not Enough. Press Enter Key To Try Again." << std::endl;
										CinBuffer_ClearOptpt('\n');
										continue;
									}
								}
								std::cout << "[Required, 1 = Quick Remind, 2 = Date-Based] Type of Reminder, Put 0 To Retain Changes |> ", std::cin >> NewModifiedTask.ReminderType;
								if (NewModifiedTask.ReminderType)
								{

									if (NewModifiedTask.ReminderType < QuickRemind || NewModifiedTask.ReminderType > DateBasedRemind || std::cin.fail())
									{
										std::cin.clear();
										std::cerr << "[INPUT ERR] |> Reminder Type Input is Invalid. Press Any Key To Try Again." << std::endl;
										CinBuffer_ClearOptpt('\n');
										_getche();
										continue;
									}
								}
								else
								{
									NewModifiedTask.ReminderType = TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderType;
								}

								switch (NewModifiedTask.ReminderType)
								{
								case QuickRemind:
									std::cout << "[Required, Min: -180, Max: 180, 0 To Retain] Minutes Left To Remind You |> ", std::cin >> NewModifiedTask.NotifyByTime;
									// TODO: Convert to time_t by mktime and return back to date time/. Done. Test Left.
									if (NewModifiedTask.NotifyByTime < -180 || NewModifiedTask.NotifyByTime > MAX_TIMELEFT)
									{
										std::cerr << "[INPUT ERR] |> Time Entered is invalid. Please try again by pressing any key to restart." << std::endl;
										CinBuffer_ClearOptpt('\n');
										_getche();
										continue;
									}
									else
									{
										if (NewModifiedTask.NotifyByTime)
										{
											// * Test Done. Success.
											CurrentDateTime = time(NULL) + (60 * NewModifiedTask.NotifyByTime);
											NewModifiedTask.TempTM = localtime(&CurrentDateTime);
											NewModifiedTask.TempTM->tm_year += 1900, NewModifiedTask.TempTM->tm_mon += 1;
											break;
										}
										else
										{
											break;
										}
									}
								case DateBasedRemind:
									CurrentDateTime = time(NULL);
									CurrentTContainer = localtime(&CurrentDateTime), CurrentTContainer->tm_year += 1900, CurrentTContainer->tm_mon += 1;

									std::cout << "[Req, Seperate by Space | MM DD YYYY] Target Date of Reminding, Type 0 For Each To Retain |> ", std::cin >> NewModifiedTask.ReminderData.tm_mon >> NewModifiedTask.ReminderData.tm_mday >> NewModifiedTask.ReminderData.tm_year;

									if (NewModifiedTask.ReminderData.tm_year < TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_year)
									{
										std::cin.clear();
										std::cerr << "[INPUT ERR] |> Target Year Parameter is either invalid or less from current date. Press Any Key To Try Again." << std::endl;
										CinBuffer_ClearOptpt('\n');
										_getche();
										continue;
									}
									else
									{
										if (NewModifiedTask.ReminderData.tm_mon < MIN_TIME_MONTH || NewModifiedTask.ReminderData.tm_mon > MAX_TIME_MONTH || NewModifiedTask.ReminderData.tm_mon < TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_mon || std::cin.fail())
										{
											std::cin.clear();
											std::cerr << "[INPUT ERR] |> Target Month Parameter is either invalid or less from current date. Press Any Key To Try Again." << std::endl;
											CinBuffer_ClearOptpt('\n');
											_getche();
											continue;
										}
										else
										{
											if (NewModifiedTask.ReminderData.tm_mday < MIN_TIME_DAY || NewModifiedTask.ReminderData.tm_mday > MAX_TIME_DAY || (NewModifiedTask.ReminderData.tm_year == TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_year && NewModifiedTask.ReminderData.tm_mon == TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_mon && (NewModifiedTask.ReminderData.tm_mday < TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_mday)) || std::cin.fail())
											{
												// ! If same month, check day.
												std::cin.clear();
												std::cerr << "[INPUT ERR] |> Target Day Parameter is either invalid or less from current date. Press Any Key To TryAgain." << std::endl;
												CinBuffer_ClearOptpt('\n');
												_getche();
												continue;
											}
										}
										std::cout << "[Req, Seperate by Space | 00:00 - 23:59] Time To Remind You |> ", std::cin >> NewModifiedTask.ReminderData.tm_hour >> NewModifiedTask.ReminderData.tm_min;

										// ! Add Some Today To Today Sens Time. Currently WORK ON PROGRESS.
										if ((NewModifiedTask.ReminderData.tm_hour > MIN_TIME_HOUR || NewModifiedTask.ReminderData.tm_hour <= MAX_TIME_HOUR) || (NewModifiedTask.ReminderData.tm_min >= MIN_TIME_MIN || NewModifiedTask.ReminderData.tm_min <= MAX_TIME_MIN) || !std::cin.fail())
										{

											// ! Prerequisite Condition, we can only get to this point if and only the datetime is exactly the same as the user added. Means 09/24/2019 == 09/24/2019. If we intend to have same date but different year then we go to else statement.

											if (NewModifiedTask.ReminderData.tm_year == TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_year && (NewModifiedTask.ReminderData.tm_mon == TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_mon && NewModifiedTask.ReminderData.tm_mday == TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_mday))
											{

												// ! Prerequisite Condition, if the datetime is exactly the same as the user added. Means 09/24/2019 == 09/24/2019. We check if the latest time is added by the user greater or less than.
												// * Exactly done conditioning.

												if (NewModifiedTask.ReminderData.tm_hour >= TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_hour)
												{
													if (NewModifiedTask.ReminderData.tm_min < TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_min)
													{
														std::cerr << "[INPUT ERR] |> Time Minute is Less Than the Expected Day. Please Try Again." << std::endl;
														CinBuffer_ClearOptpt('\n');
														_getche();
														continue;
													}
													else
													{
														break;
													}
												}
												else
												{
													std::cerr << "[INPUT ERR] |> Time Hour is Lesser Than Expected Hour. Please Try Again." << std::endl;
													CinBuffer_ClearOptpt('\n');
													_getche();
													continue;
												}
											}
											else
											{
												// ! We proceed as there will be no conflict at timing.
												break;
											}
										}
										else
										{
											std::cin.clear();
											std::cerr << "[INPUT ERR] |> Time Input is Invalid. Keep in mind that I need 24 hour format. Press Any Key To Try Again." << std::endl;
											CinBuffer_ClearOptpt('\n');
											_getche();
											continue;
										}
										break;
									}
									break;
								}
								try
								{
									if (NewModifiedTask.TaskName != "0")
									{
										TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName.assign(NewModifiedTask.TaskName);
									}
									else
									{
										NewModifiedTask.TaskName.assign(TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName);
									}

									if (NewModifiedTask.TaskInCharge != "0")
									{
										TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskInCharge.assign(NewModifiedTask.TaskInCharge);
									}
									else
									{
										NewModifiedTask.TaskInCharge.assign(TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskInCharge);
									}

									if (NewModifiedTask.ReminderType != TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderType)
									{
										TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderType = NewModifiedTask.ReminderType;
									}
									else
									{
										NewModifiedTask.ReminderType = TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderType;
									}

									switch (NewModifiedTask.ReminderType)
									{
									// ! Clear Some Other Variable When That CASE is not using that variable.
									case QuickRemind:
										if (NewModifiedTask.NotifyByTime != 0)
										{
											TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData = *NewModifiedTask.TempTM;
										}
										else
										{
											NewModifiedTask.ReminderData = TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData;
										}
										break;

									case DateBasedRemind:
										if (NewModifiedTask.ReminderData.tm_year != 0)
										{
											TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_year = NewModifiedTask.ReminderData.tm_year;
										}
										else
										{
											NewModifiedTask.ReminderData.tm_year = TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_year;
										}

										if (NewModifiedTask.ReminderData.tm_mon != 0)
										{
											TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_mon = NewModifiedTask.ReminderData.tm_mon;
										}
										else
										{
											NewModifiedTask.ReminderData.tm_mon = TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_mon;
										}

										if (NewModifiedTask.ReminderData.tm_mday != 0)
										{
											TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_mday = NewModifiedTask.ReminderData.tm_mday;
										}
										else
										{
											NewModifiedTask.ReminderData.tm_mday = TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_mday;
										}

										if (NewModifiedTask.ReminderData.tm_hour != 0)
										{
											TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_hour = NewModifiedTask.ReminderData.tm_hour;
										}
										else
										{
											NewModifiedTask.ReminderData.tm_hour = TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_hour;
										}

										if (NewModifiedTask.ReminderData.tm_min != 0)
										{
											TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_min = NewModifiedTask.ReminderData.tm_min;
										}
										else
										{
											NewModifiedTask.ReminderData.tm_min = TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).ReminderData.tm_min;
										}
										break;
									}

									SaveStateHandler.open(SaveStatePath, std::ios::in);
									TempSaveStateHandler.open(SaveStatePath, std::ios::out);

									while (!SaveStateHandler.eof())
									{
										PayloadHandler.clear();
										std::getline(SaveStateHandler, DataLineHandler);
										std::stringstream TempDataHandler(DataLineHandler);

										for (DataLineHandler; std::getline(TempDataHandler, ConvertedHandler, ','); PayloadHandler.push_back(ConvertedHandler))
											;

										if (PayloadHandler[0] != TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName)
										{
											for (IterHandler_UnSh = INIT_NULL_INT; IterHandler_UnSh < PayloadHandler.size(); IterHandler_UnSh++)
											{
												TempSaveStateHandler << PayloadHandler[IterHandler_UnSh] << (IterHandler_UnSh == (PayloadHandler.size() - POS_OFFSET_BY_ONE) ? "\n" : ",");
											}
										}
										else
										{
											if (NewModifiedTask.ReminderType == QuickRemind)
											{
												TempSaveStateHandler << NewModifiedTask.TaskName << "," << NewModifiedTask.TaskInCharge << "," << NewModifiedTask.ReminderType << "," << mktime(NewModifiedTask.TempTM) << std::endl;
											}
											else
											{
												NewModifiedTask.ReminderData.tm_year -= 1900, NewModifiedTask.ReminderData.tm_mon -= 1, NewModifiedTask.ReminderData.tm_sec = 0;
												TempSaveStateHandler << NewModifiedTask.TaskName << "," << NewModifiedTask.TaskInCharge << "," << NewModifiedTask.ReminderType << "," << mktime(&NewModifiedTask.ReminderData) << std::endl;
											}
										}
									}

									SaveStateHandler.close();
									TempSaveStateHandler.close();

									remove(SaveStatePath);
									rename(FilePointState, SaveStatePath);

									std::cout << "[Confirmation, Success] |> Task Modification @ '" << TaskList.at(handleInputInt - POS_OFFSET_BY_ONE).TaskName << "' is now applied~!" << std::endl;
									delay_time(SLEEP_OPRT_FINISHED);
									continue;
								}
								catch (...)
								{
									std::cout << std::endl
											  << "[PROCESS] Unknown error has occured..." << std::endl;
									delay_time(SLEEP_SIGNIFICANT_ERR);
									continue;
								}

							case CONFIRMED_FALSE_LOWER:
							case CONFIRMED_FALSE_UPPER:
								std::cout << "[Confirmation, Success] |> Task Deletion Cancelled." << std::endl;
								delay_time(SLEEP_OPRT_FINISHED);
								continue;

							default:
								std::cout << "[Confirmation, Error] |> User Input Invalid." << std::endl;
								std::cin.clear();
								CinBuffer_ClearOptpt('\n');
								delay_time(SLEEP_OPRT_FAILED);
								continue;
							}
						}
					}
					else
					{
						std::cerr << "[Input Error] |> User Requested To Delete Tasks Non-Existent or Out of Range..." << std::endl;
						delay_time(SLEEP_ERROR_PROMPT);
						continue;
					}
				}
				else
				{
					break;
				}
			}
		}
		else
		{
			std::cerr << "[View Info] > Task Queue is currently empty! Please add some task/s." << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			break;
		}
	}
	return;
}
void TTRM::MenuSel_VTask() noexcept(false)
{
	while (PROCESS_AWAIT_CMPLT)
	{
		WinCall_CMD("CLS");
		//std::cout << std::endl
		//		  << "Here are the tasks currently in line with the system..." << std::endl;
		DisplayTasks_AtWindow(ViewTask);
		std::cout << "Press any key to go back." << std::endl;
		_getche();
		break;
	}
	return;
}

void TTRM::MenuSel_RQT() noexcept(false)
{

	if (TaskList.size())
	{
		std::cout << std::endl
				  << "[WARNING] |> Are you sure you want delete all tasks in queue system?" << std::endl
				  << "[WARNING] |> All task can be restored if the database still contains all data you just deleted." << std::endl
				  << "[INPUT  ] |> ['Y'es or 'N'o] |> ",
			std::cin >> handleInputChar;
		switch (handleInputChar)
		{
		case CONFIRMED_TRUE_LOWER:
		case CONFIRMED_TRUE_UPPER:
			remove(SaveStatePath);
			SaveStateHandler.open(SaveStatePath, std::ios::out);
			SaveStateHandler.close();
			TaskList.clear();
			std::cout << "[PROCESS] |> All Task from Queue Removed!" << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			break;
		case CONFIRMED_FALSE_LOWER:
		case CONFIRMED_FALSE_UPPER:
			std::cout << "[PROCESS] |> All Task Deletion Operation Cancelled." << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			break;
		default:
			std::cin.clear();
			CinBuffer_ClearOptpt('\n');
			std::cout << "[ERROR  ] |> Invalid Input. All Task Deletion Operation Cancelled." << std::endl;
			delay_time(SLEEP_OPRT_FINISHED);
			break;
		}
		return;
	}
	else
	{
		std::cerr << std::endl
				  << "[INFORM ] Your Task List is empty! Please add one." << std::endl;
		delay_time(SLEEP_OPRT_FINISHED);
		return;
	}
}

// CORE FUNCTION CONTENT DECLARATION - END POINT

//----------------------------------------------------------------------------

// TECHNICAL FUNCTION CONTENT DECLARATION - STARTING POINT

/*
    Technical Project Specific Essential Function CPP File by Janrey "CodexLink" Licas
    File Category Type: Core Function Body Definition, "CoreFunc".
	Note that this CPP file will only contain external library functions.
*/

// WinToast FUNCTION CONTENT DECLARATION - STARTING POINT

void TTRM_WinToast::toastActivated() const
{

	std::wcout << L"The user clicked in this toast" << std::endl;
}
void TTRM_WinToast::toastActivated(int actionIndex) const
{

	std::wcout << L"The user clicked on action #" << actionIndex << std::endl;
	//	exit(16 + actionIndex);
}
void TTRM_WinToast::toastDismissed(WinToastDismissalReason state) const
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
void TTRM_WinToast::toastFailed() const
{
	;
	//	std::wcout << L"Error showing current toast" << std::endl;
	//	exit(5);
}

// WinToast FUNCTION CONTENT DECLARATION - END POINT

// TECHNICAL FUNCTION CONTENT DECLARATION - END POINT

//----------------------------------------------------------------------------