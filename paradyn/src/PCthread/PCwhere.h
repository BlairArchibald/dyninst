/*
 * 
 * $Log: PCwhere.h,v $
 * Revision 1.1  1994/02/02 00:38:23  hollings
 * First version of the Performance Consultant using threads.
 *
 * Revision 1.8  1993/08/05  19:00:59  hollings
 * new includes.
 *
 * Revision 1.7  1993/05/07  20:19:17  hollings
 * Upgrade to use dyninst interface.
 *
 * Revision 1.6  1993/03/23  17:17:40  hollings
 * changed testValue's friendship.
 *
 * Revision 1.5  1993/02/03  00:06:49  hollings
 * removed execesive friends of focus and focusCell.
 *
 * Revision 1.4  1992/12/14  19:58:27  hollings
 * added true enable/disable.
 *
 * Revision 1.3  1992/10/23  20:13:37  hollings
 * Working version right after prelim.
 *
 * Revision 1.2  1992/08/24  15:12:20  hollings
 * first cut at automated refinement.
 *
 * Revision 1.1  1992/08/03  20:45:54  hollings
 * Initial revision
 *
 *
 */

#ifndef FOCUS_H
#define FOCUS_H

#include "util/h/list.h"
#include "util/h/stringPool.h"
#include "dataManager.h"

extern class PCmetric;
extern class testValue;
extern class focus;
extern class searchHistoryNode;
class focusList;

//
// A point along the where axis.
//
class focus {
	friend class testValue;
    public:
	focus();		
	focus(resourceList*);
	focusList magnify(resource *param);
	focusList enumerateRefinements();
	focus *constrain(resource *param);

	Boolean operator ==(focus*);	// comparison
	focus *moreSpecific(resource *parm);
	operator =(focus);
	void print(char*);
	void print();
	void updateName();
	stringHandle getName() 	{ return(name); }

	resourceList *data;
    private:
	// internal helper methods.
	focusList *findMagnifyCache(resource*);
	void addMagnifyCache(resource*, focusList*);

	focus *findConstrainCache(resource*);
	void addConstrainCache(resource*, focus*);

	stringHandle name;		// for fast compare.
	List<focusList*>		magnifyCache;
	List<focus*>			constrainCache;
};

class focusList: public HTable<focus*> {
    public:
	focusList(focus *f) { focusList(); add(f,f->getName()); }
	focusList() {  HTable<focus*>(); }
	focus *find(focus *f) { return(find(f->getName())); }
	Boolean addUnique(focus *f) { return(addUnique(f, f->getName())); }
};

extern stringPool strSpace;

// current global focus
extern focus *whereAxis;

// current set of foci.
extern focusList globalFocus;

// 
extern resource *rootResource;

// current focus
extern focus *currentFocus;

// all knwon focii.
extern focusList allFoci;

extern resource *Locks;
extern resource *Barriers;
extern resource *Semaphores;

extern resource *SyncObject;
extern resource *Procedures;
extern resource *Processes;
extern resource *Machines;

#endif
