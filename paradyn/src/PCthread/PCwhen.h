/*
 *
 * $Log: PCwhen.h,v $
 * Revision 1.1  1994/02/02 00:38:22  hollings
 * First version of the Performance Consultant using threads.
 *
 * Revision 1.4  1993/08/05  19:00:47  hollings
 * added new includes.
 *
 * Revision 1.3  1993/05/07  20:19:17  hollings
 * Upgrade to use dyninst interface.
 *
 * Revision 1.2  1992/10/23  20:13:37  hollings
 * Working version right after prelim.
 *
 * Revision 1.1  1992/08/24  15:12:20  hollings
 * Initial revision
 *
 *
 * Interface to when (Temporal) axis.
 *
 */
#ifndef WHEN_H
#define WHEN_H

#include "util/h/list.h"

extern class timeInterval;
typedef List<timeInterval*> timeIntervalList;

class timeInterval {
	friend void doLoad(int, int*);
    public:
	timeInterval(timeInterval*, timeStamp, timeStamp, char*);
	void print(int);
	void print(int, char *name);
	timeStamp start;
	timeStamp end;
	int id;
	timeIntervalList *subIntervals;
	char *getName() { return(name); }
    private:
	char *name;
};

extern timeInterval *currentInterval;		// currentInterval being tested.
extern timeInterval whenAxis;			// root of when axis.

extern timeIntervalList allTimeIntervals;	// list of all when nodes.

#endif /* WHEN_H */
