#include <iostream>
#include <string>
#include <vector>
#include "queue.h"
/* 
Implementation of queue.h class
*/

//Description: Queue constructor with no parameters
Queue::Queue()
{
	front = 0;
	back = 0;
	name = "QueueHasNoName";
	serviceRate = 1;
	systemTime = 0;
	length = 0;
	serviceStationOpen = 1;
	jobCount = 0;
	incrementTimeAfterJobCompletion = false;
}

//Description: Queue constructor with time set
Queue::Queue(int time)
{
	//Make front and back point to null
	front = 0;
	back = 0;
	name = "QueueHasNoName";
	serviceRate = 1;
	systemTime = time;
	length = 0;
	serviceStationOpen = 1;
	jobCount = 0;
	incrementTimeAfterJobCompletion = false;
}

//Description: Loads the queue with a job using just job size
void Queue::enqueue(int jobSize)
{
	if (length == 0)
	{
		Queue::jobData *newJob = new Queue::jobData;
		jobCount++;
		newJob->jobName = "";
		newJob->jobNumber = jobCount;
		newJob->jobSize = jobSize;
		newJob->queueEntryTime = systemTime;
		newJob->queueExitTime = 0;
		newJob->serviceEntryTime = 0;
		newJob->serviceExitTime = 0;
		newJob->next = 0;
		front = newJob;
		back = newJob;
		length++;		
	}
	else
	{
		Queue::jobData *newJob = new Queue::jobData;
		jobCount++;
		newJob->jobName = "";
		newJob->jobNumber = jobCount;
		newJob->jobSize = jobSize;
		newJob->queueEntryTime = systemTime;
		newJob->queueExitTime = 0;
		newJob->serviceEntryTime = 0;
		newJob->serviceExitTime = 0;
		newJob->next = 0;
		back->next = newJob;
		back = back->next;
		length++;
	}

}

//Description: Just another name for enqueue. Calls void enqueue(int)
void Queue::insert(int jobSize)
{
	enqueue(jobSize);
}

//Description: Removes and returns the job at the front of the queue; returns the dummy job is queue is empty
Queue::jobData Queue::dequeue()
{
	/*If queue is empty, create and return a dummy job*/
	if (length == 0)
	{
		Queue::jobData *dummyJob = new Queue::jobData;
		dummyJob->jobName = "000000";
		dummyJob->jobSize = 0;
		dummyJob->queueEntryTime = 0;
		dummyJob->queueExitTime = 0;
		dummyJob->serviceEntryTime = 0;
		dummyJob->serviceExitTime = 0;
		return *dummyJob;
		delete dummyJob;
	}
	else
	{
		/*Create temporary job, load with front job's data, return it, move front pointer
		Dequeue to a temp holding job that will be picked up by the service station*/
		Queue::jobData *tempJob = new Queue::jobData;
		*tempJob = getFront();
		tempJob->queueExitTime = systemTime;
		tempJob->serviceEntryTime = systemTime;
		temp = front;
		front = front->next;
		temp->next = 0;
		length--;
		tempHoldingJob = *tempJob;
		serviceStationOpen = 0;
		return *tempJob;
		delete tempJob;
	}
}

//Description: Just another name for dequeue. Calls jobData dequeue(), and returns what jobData dequeue() returns
Queue::jobData Queue::remove()
{
	return dequeue();
}


//Description: Sets the rate at which jobs get completed per unit time
void Queue::setServiceRate(int rate)
{
	serviceRate = rate;
}

//Description: Sets the system time i.e. the queue's time.
void Queue::setSystemTime(int time)
{
	systemTime = time;
}

//Description: Sets the name of the queue
void Queue::setName(std::string aName)
{
	name = aName;
}

//Description: Sets whether queue increments time after a job is completed
void Queue::setIncrementTimeOption(bool option)
{
	incrementTimeAfterJobCompletion = option;
}

//Description: Sets the time at which the queue will be recorded to have begun operating. Works with void modifyTime()
void Queue::setBeginningHour(int beginHour)
{
	beginningHour = beginHour;
}

//Description: Returns the rate at which jobs get completed per unit time
int Queue::getServiceRate()
{
	return serviceRate;
}

//Description: Returns the queue's time
int Queue::getSystemTime()
{
	return systemTime;
}

//Description: Returns the name of the queue
std::string Queue::getName()
{
	return name;
}

//Description: Returns whether queue increments time after a job is completed
bool Queue::getIncrementTimeOption()
{
	return incrementTimeAfterJobCompletion;
}


int Queue::getBeginningHour()
{
	return beginningHour;
}


//Description: Returns the time at which the queue will be recorded to have begun operating. Works with void modifyTime()
Queue::jobData Queue::getFront()
{
	//If queue is empty, create and return a dummy job
	if (length == 0)
	{
		Queue::jobData *dummyJob = new Queue::jobData;
		dummyJob->jobName = "000000";
		dummyJob->jobSize = 0;
		dummyJob->queueEntryTime = 0;
		dummyJob->queueExitTime = 0;
		dummyJob->serviceEntryTime = 0;
		dummyJob->serviceExitTime = 0;
		return *dummyJob;
		delete dummyJob;
	}
	return *front;
}

//Description: Returns the job in the back of the queue in jobData format
Queue::jobData Queue::getBack()
{
	//If queue is empty, create and return a dummy job
	if (length == 0)
	{
		Queue::jobData *dummyJob = new Queue::jobData;
		dummyJob->jobName = "000000";
		dummyJob->jobSize = 0;
		dummyJob->queueEntryTime = 0;
		dummyJob->queueExitTime = 0;
		dummyJob->serviceEntryTime = 0;
		dummyJob->serviceExitTime = 0;
		return *dummyJob;
		delete dummyJob;
	}
	else
		return *back;
}

//Description: Returns the number of jobs in (length of) the queue
int Queue::getLength()
{ 
	return length;
}

//Description: Returns the total queue time of all completed jobs
int Queue::getTotalQueueTime()
{
	int totalQueueTime = 0;

	for (int i = 0; i < completedJobs.size(); i++)
	{
		totalQueueTime = totalQueueTime + completedJobs[i].getQueueTime();
	}

	return totalQueueTime;
}


//Description: Returns the total service time of all completed jobs
int Queue::getTotalServiceTime()
{
	int totalServiceTime = 0;

	for (int i = 0; i < completedJobs.size(); i++)
	{
		totalServiceTime = totalServiceTime + completedJobs[i].getServiceTime();
	}

	return totalServiceTime;
}

//Description: Returns true if queue is empty, otherwise returns false
bool Queue::isEmpty()
{
	if ((front == 0) && (back == 0))
		return true;
	else
		return false;
}

//Description: Prints information of all completed jobs
void Queue::printAllCompletedJobs()
{ 
	std::cout << "STARTED AT " << beginningHour << ":00. USING 24-HR TIME. " << std::endl;
	std::cout << std::endl;

	for (int i = 0; i < completedJobs.size(); i++)
	{
		std::cout << "Job name: " << completedJobs[i].jobName << std::endl;
		std::cout << "Job number: " << completedJobs[i].jobNumber << std::endl;
		//std::cout << "Job size: " << completedJobs[i].jobSize << std::endl;
		std::cout << "Queue Entry Time: ";
		modifyTime(completedJobs[i].queueEntryTime); 
		std::cout << std::endl;
		std::cout << "Queue Exit Time: ";
		modifyTime(completedJobs[i].queueExitTime);
		std::cout << std::endl;
		std::cout << "Job's Queue Time: " << completedJobs[i].getQueueTime() << std::endl;
		std::cout << "Service Entry Time: ";
		modifyTime(completedJobs[i].serviceEntryTime); 
		std::cout << std::endl;
		std::cout << "Service Exit Time: ";
		modifyTime(completedJobs[i].serviceExitTime);
		std::cout << std::endl;
		std::cout << "Job's Service Time: " << completedJobs[i].getServiceTime() << std::endl;
		std::cout << std::endl;
	}
}

//Description: Increments the system time by 1
void Queue::incrementSystemTime()
{
	systemTime++;
}

//Description: Sends address of job just dequeued (tempHoldingJob) to serviceStation(pointer to jobData) to work on job. 
void Queue::workOnJob()
{
	serviceStation(&tempHoldingJob);
}

//Description: Returns 1 if serviceStation can accept jobs, 0 if it can't accept any jobs
int Queue::isServiceStationOpen()
{
	return serviceStationOpen;
}

//Processes jobs by decreasing their job size by service rate
void Queue::serviceStation(Queue::jobData* job)
{
		job->jobSize = job->jobSize - serviceRate;
		
		if (incrementTimeAfterJobCompletion)
			systemTime++;	
	
	if (job->jobSize == 0)
	{		
		job->serviceExitTime = systemTime;

		/*Output job number and queue time*/
		std::cout << std:: endl;
		std::cout << "Job number " << job->jobNumber << " completed."<< std::endl;
		std::cout << "Job spent " << job->getQueueTime() << " minutes in the queue."<< std::endl;
		
		/*Place job in vector */
		Queue::completedJobs.push_back(*job);

		/*Reset temporary holding job*/
		tempHoldingJob.jobName = "";
		tempHoldingJob.jobNumber = 0;
		tempHoldingJob.jobSize = 0;
		tempHoldingJob.queueEntryTime = 0;
		tempHoldingJob.queueExitTime = 0;
		tempHoldingJob.serviceEntryTime = 0;
		tempHoldingJob.serviceExitTime = 0;
		tempHoldingJob.next = 0;

		/*Accept jobs in service station*/
		serviceStationOpen = 1; 

		
	}
			
}

//Description: Displays time in hour:minute format
void Queue::modifyTime(int time)
{
	int hours = 0;
	int min = 0;
	int newHour = 0;

	hours = time/60;
	min = time % 60;

	newHour = hours + beginningHour;

	if (newHour >= 24)	
		newHour = (newHour - 24);

	if (min < 10)
		std::cout << newHour << ":0" << min;
	else
		std::cout << newHour << ":" << min;
	
	
}
