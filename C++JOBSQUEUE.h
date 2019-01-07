#ifndef QUEUE_H
#define QUEUE_H

#include <vector>
#include <string>

class Queue
{
	private:
		
		struct jobData											//A job data structure
		{
			std::string jobName;								//Holds a job's name
			int jobNumber;										//Each jobs has a number to help with count
			int jobSize;										//How long it takes to do a job
			int queueEntryTime;									//Recorded when a job enters the queue								
			int queueExitTime;									//Recorded when a job exists the queue
			int serviceEntryTime;								//Recorded when a job starts to get service
			int serviceExitTime;								//Recorded when a job is finished
			
			/*
			Description: Calculates and returns an individual job's queue time
			Preconditions: variables queueExitTime and queueEntryTime must exist and be integers
			Postconditions: job's queue time will be returned
			*/
			int getQueueTime()									
			{
				return (queueExitTime - queueEntryTime);
			}
			
			/*
			Description: Calculates and returns an individual job's service time
			Preconditions: variables serviceExitTime and serviceEntryTime must exist and be integers
			Postconditions: job's service time will be returned
			*/
			int getServiceTime()								
			{
				return (serviceExitTime - serviceEntryTime);
			}
			struct jobData* next;								//Pointers used to point to the next job
		};

		jobData* front;											//Queue's front pointer
		jobData* back;											//Queue's back pointer
		jobData* temp;											//Queue's temporary pointer
		jobData tempHoldingJob;									//Job data structure used to temporarily hold jobs
		std::string name;										//Name of the queue
		int serviceRate;										/*The rate at which the queue processes a job per unit time. 
																 Default is 1. 1 job processed per unit time */
		
		int systemTime;											//The queue's time
		int length;												//The queue's length (number of jobs in the queue)
		int serviceStationOpen;									//Signals whether the service station is ready to process
		int jobCount;											//Counts the total number of jobs processed
		bool incrementTimeAfterJobCompletion;					/*Stores option to increment system time right after a job is finished
																 Default is false*/
		int beginningHour;										//Hour at which queue starts to operate, default is 0
		
		/*
		Description: //Processes jobs by decreasing their job size by the service rate
		Preconditions: pointer to a job in jobData format must be passed and be valid
		Postconditions: job's jobSize will be decreased by service rate, if jobSize is zero, the job will be placed in
		the completedJobs vector
		*/
		void serviceStation(jobData*);							//Service station processes jobs right after they have been dequeued
						
	public:
		/*
		Description: Queue constructor with no parameters
		Preconditions: Queue of the same name must not exist
		Postconditions: Queue will exist once instantiated, with variables below
		*/
		Queue(); 												
		
		/*
		Description: Queue constructor with time set
		Preconditions: Queue of the same name must not exist
		Postconditions: Queue will exist once instantiated, with variables below
		*/
		Queue(int);												
		
		/*
		Description: Loads the queue with a job using just job size
		Preconditions: jobSize must be an integer
		Postconditions: Queue will contain a job structure with the integer as its job size
		*/
		void enqueue(int); 										
		
		/*
		Description: Just another name for enqueue. Calls void enqueue(int)
		Preconditions: void enqueue(int) must exist and functioning properly
		Postconditions: Queue will contain a job structure with the integer as its job size
		*/
		void insert(int); 										
		
		/*
		Description: Removes and returns the job at the front of the queue; returns the dummy job is queue is empty
		Preconditions: Queue must exist and have been instantiated
		Postconditions: If queue has any jobs in it, the job at the front of the queue will be removed
		*/
		jobData dequeue();		

		/*
		Description: Just another name for dequeue. Calls jobData dequeue(), and returns what jobData dequeue() returns
		Preconditions: jobData dequeue() must exist and functioning properly
		Postconditions: If queue has any jobs in it, the job at the front of the queue will be removed
		*/
		jobData remove(); 										
		
		/*
		Description: Sets the rate at which jobs get completed per unit time
		Preconditions: queue must have already been instantiated; rate must be an integer
		Postconditions: The queue's service rate will be rate
		*/
		void setServiceRate(int);		

		/*
		Description: Sets the system time i.e. the queue's time.
		Preconditions: queue must have already been instantiated; time must be an integer
		Postconditions: The queue's time will be time
		*/
		void setSystemTime(int); 	

		/*
		Description: Sets the name of the queue
		Preconditions: queue must have already been instantiated; aName must be a string
		Postconditions: queue will contain the name in aName
		*/
		void setName(std::string);			

		/*
		Description: Sets whether queue increments time after a job is completed
		Preconditions: option must be in boolean format
		Postconditions: incrementTimeAfterJobCompletion will be set to option
		*/
		void setIncrementTimeOption(bool);

		/*
		Description: Sets the time at which the queue will be recorded to have begun operating. Works with void modifyTime()
		Preconditions: beginningHour must exist and must be an integer
		Postconditions: beginningHour will be set to beginHour
		*/
		void setBeginningHour(int);								
		
		/*
		Description: Returns the rate at which jobs get completed per unit time
		Preconditions: queue must have already been instantiated; serviceRate must be an integer
		Postconditions: serviceRate will be returned
		*/
		int getServiceRate(); 

		/*
		Description: Returns the queue's time
		Preconditions: queue must have already been instantiated; systemTime must be an integer
		Postconditions: systemTime will be returned
		*/
		int getSystemTime();
			
		/*
		Description: Returns the name of the queue
		Preconditions: queue must have already been instantiated; name must be a string
		Postconditions: name will be returned
		*/
		std::string getName();

		/*
		Description: Returns whether queue increments time after a job is completed
		Preconditions: incrementTimeAfterJobCompletion must be in boolean format
		Postconditions: incrementTimeAfterJobCompletion will be returned
		*/
		bool getIncrementTimeOption();

		/*
		Description: Returns the time at which the queue will be recorded to have begun operating. Works with void modifyTime()
		Preconditions: beginningHour must exist and must be an integer
		Postconditions: beginningHour will be returned
		*/
		int getBeginningHour();	
		
		/*
		Description: Returns the job in the front of the queue in jobData format
		Preconditions: front must be in jobData format
		Postconditions: If queue is empty, a dummy job will be returned, otherwise the job at the front of the queue will be returned
		*/
		jobData getFront();										
		
		/*
		Description: Returns the job in the back of the queue in jobData format
		Preconditions: back must be in jobData format
		Postconditions: If queue is empty, a dummy job will be returned, otherwise the job at the back of the queue will be returned
		*/
		jobData getBack();

		/*
		Description: Returns the number of jobs in (length of) the queue
		Preconditions: queue must have already been instantiated; length must be an integer
		Postconditions: length will be returned
		*/
		int getLength();
		
		/*
		Description: Returns the total queue time of all completed jobs
		Preconditions: completedJobs must exist and must be a vector designed to store variables in jobData format.
						getQueueTime() must be a function in a job and must return an integer
		Postconditions: The total queueTime of all jobs in the completedJobs vector will be returned
		*/
		int getTotalQueueTime();

		/*
		Description: Returns the total service time of all completed jobs
		Preconditions: completedJobs must exist and must be a vector designed to store variables in jobData format
						getServiceTime() must be a function in a job and must return an integer
		Postconditions: The total serviceTime of all jobs in the completedJobs vector will be returned
		*/
		int getTotalServiceTime();								
		
		/*
		Description: Returns true if queue is empty, otherwise returns false
		Preconditions: jobData front and jobData back must exist
		Postconditions: Will return true if front and back point to null, otherwise, it will return false
		*/
		bool isEmpty();

		/*
		Description: Prints information of all completed jobs
		Preconditions: completedJobs must exist and must be a vector designed to store variables in jobData format
		Postconditions: All completed jobs will be printed to screen,otherwise, a 0 will be printed
		*/
		void printAllCompletedJobs();							
		
		/*
		Description: Increments the system time by 1
		Preconditions: systemTime must exist, and must be an integer
		Postconditions: systemTime's value will be increased by 1
		*/
		void incrementSystemTime();								
		
		/*
		Description: Sends address of job just dequeued (tempHoldingJob) to serviceStation(pointer to jobData) to work on job. 
		(Written to fulfill assignment requirements)
		Preconditions: tempHoldingJob must exist and must contain information about the job just dequeued
		Postconditions: serviceStation will be called and will receive the address of the job just dequeued
		*/
		void workOnJob();

		/*
		Description: Returns 1 if serviceStation can accept jobs, 0 if it can't accept any jobs
		Preconditions: serviceStationOpen must be an integer
		Postconditions: integer value of serviceStationOpen will be returned
		*/
		int isServiceStationOpen();								
		
		/*
		Description: Works on a job by decreasing its jobSize by the service rate
		Preconditions: Job must be passed by reference
		Postconditions: Job's job size will be decreased to zero and job's data will be placed in vector completedJobs
		*/
		std::vector<jobData>completedJobs;						
		
		/*
		Description: Displays time in hour:minute format
		Preconditions: time must be an integer, beginningHour must exist and must be an integer
		Postconditions: hours and minutes after beginningHour will be displayed to screen
		*/
		void modifyTime(int);									
};

#endif
