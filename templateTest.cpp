#include "etss.h"
#include "atpPingTest.h"
#include "Queue.h"
#include "ATP_LOG_REC.h"

extern BLIST::Queue<ATP_LOG_REC> theQs[ATP_TEST_MAX];
//TODO: Place any member function defenitions here
void ETSS::etss::atpTemplateTest(ARGS::ATP_ARG arg)
{
	//templateTest test_obj;
	//or
	//int errorflag = 0;

	unsigned int cnt = 0;			// loop counter 
	unsigned int errCnt = 0;			// loop counter 
	bool errFlag = false;		// error flag 
	int tid = arg.get_tid();
	bool stopOnErr = arg.get_stopOnErr();
	ATP_LOG_REC testresult;

	//TODO: Add your Test specific initializations here

	while (true)
	{
		cnt++;
		std::cout << "template device to be tested " << arg.get_devname() << " this is where your test goes" << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		//TODO: your test goes here
		// if (test_obj.thetest(arg.get_devname()) != 0)
		// or
		if (errorflag != 0)
		{
			//atpLog(atpMsgWarn, tid, atpErrPing, 0, cnt, 0);
			testresult.tid = tid;
			testresult.err = 3;
			testresult.cnt = cnt;
			theQs[tid-1].enqueue(testresult);
			errFlag = true;
			if (errFlag) 
			{
				errCnt++;
				if (stopOnErr) 
				{
					etss::atpStatusSetStatic(tid, false);
					break;
				} 
				else 
				{
					errFlag = false;
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				}
			}
		}
		else
		{
			testresult.tid = tid;
			testresult.err = 0;
			testresult.cnt = cnt;
			theQs[tid-1].enqueue(testresult);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
		if (!etss::atpStatusCheckStatic(tid)) 
		{
			std::cout << "atptemplate: atpStatusCheck returned FALSE" << std::endl;
			std::cout << "atptemplate: TERMINATING TASK\n" << std::endl;
			break;
		}
	}
}
