/*
 * Mutex.h
 */


#ifndef _Mutex_h_included_
#define _Mutex_h_included_

#include <string>
#include <pthread.h>

/**Implements a Mutual Exclusion for proper access of a resource.*/
class Mutex
{
protected:
    /**The mutex ID.*/
    pthread_mutex_t work_mutex;
    
    /**A small function to display messages.
     * @param msg The message string to show.
     */
    void showMessage(string msg)
	{
            cerr << "Mutex: " << msg;
	}


public:
    /**Constructor which sets up the mutex.*/
    Mutex(void)
        {

            int res;
            res = pthread_mutex_init(&this->work_mutex, NULL);
            if (res != 0)
            {
                showMessage("Mutex initialization failed");
                exit(EXIT_FAILURE);
            }
	}
    /**Use to lock a resource.*/
    void lock(void)
	{
            pthread_mutex_lock(&this->work_mutex);
	}
    /**Use to unlock a resource.*/
    void unlock(void)
        {
            pthread_mutex_unlock(&this->work_mutex);
	}
};

#endif
