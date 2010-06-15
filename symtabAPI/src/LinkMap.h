/*
 * Copyright (c) 1996-2010 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#if !defined(_Link_Map_h_)
#define _Link_Map_h_

#include "Symtab.h"
#include "Region.h"
#include "Symbol.h"
#include "Function.h"

#include <deque>
#include <map>
#include <vector>
using namespace std;

namespace Dyninst{
namespace SymtabAPI{

/*
 * A data structure that holds all the information necessary to perform a
 * static link once all the relocatable files have been copied into a new data
 * block
 */
class LinkMap {
    public:
        LinkMap();
        ~LinkMap();

        // A pair representing an allocation for a Region
        // The first Offset is the amount of padding before the Region
        // The second Offset is the offset of the location in the allocatedData
        typedef pair<Offset, Offset> AllocPair;

        // prints the LinkMap (really for debugging purposes)
        // uses globalOffset as the location of allocatedData in the target
        void print(Offset globalOffset);
        void printAll(ostream &os, Offset globalOffset);
        void printBySymtab(ostream &os, vector<Symtab *> &symtabs, Offset globalOffset);
        void printRegions(ostream &os, deque<Region *> &regions, Offset globalOffset);
        void printRegion(ostream &os, Region *region, Offset globalOffset);
        void printRegionFromInfo(ostream &os, Region *region, Offset regionOffset, Offset padding);
        
        friend ostream & operator<<(ostream &os, LinkMap &lm);

        // Data Members
        // all other members describe this block of data
        char *allocatedData; 
        Offset allocatedSize;

        // map of Regions placed in allocatedData
        map<Region *, AllocPair> regionAllocs;

        // Keep track of the dynamically allocated COMMON symbol Region
        Region *commonStorage;

        // new Region info
        // Offset -> offset in allocatedData
        // Size -> size of Region
        // Regions -> existing Regions which make up this Region

        // new bss Region info
        Offset bssRegionOffset;
        Offset bssSize;
        Offset bssRegionAlign;
        deque<Region *> bssRegions;

        // new data Region info
        Offset dataRegionOffset;
        Offset dataSize;
        Offset dataRegionAlign;
        deque<Region *> dataRegions;
        
        // new code Region info
        Offset codeRegionOffset;
        Offset codeSize;
        Offset codeRegionAlign;
        deque<Region *> codeRegions;
        
        // new TLS Region info
        Offset tlsRegionOffset;
        Offset tlsSize;
        Offset tlsRegionAlign;
        deque<Region *> tlsRegions;
        vector<Symbol *> tlsSymbols;

        // new GOT Region info
        Offset gotRegionOffset;
        Offset gotSize;
        Offset gotRegionAlign;
        map<Symbol *, Offset> gotSymbols;

        Symtab *ctorDtorHandler;

        // new constructor Region info
        Offset ctorRegionOffset;
        Offset ctorSize;
        Offset ctorRegionAlign;
        Region *originalCtorRegion;
        vector<Region *> newCtorRegions;

        // new destructor Region info
        Offset dtorRegionOffset;
        Offset dtorSize;
        Offset dtorRegionAlign;
        Region *originalDtorRegion;
        vector<Region *> newDtorRegions;

        // Keep track of changes made to symbols and relocations
        vector< pair<Symbol *, Offset> > origSymbols;
        vector< pair<relocationEntry *, Symbol *> > origRels;
};

} // SymtabAPI
} // Dyninst

#endif