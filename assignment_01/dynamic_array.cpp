#include <iostream>										//-
#include <string.h>										//-
#include "dynamic_array.h"									//-
												//-
using namespace std;										//-
												//-
// ********** public functions **********							//-
												//-
Dynamic_array::Dynamic_array() {								//-
	head_p = NULL;										//-
	size = 0;										//-
}												//-
												//-
Dynamic_array::Dynamic_array(Dynamic_array & d) {						//-
}												//-
												//-
Dynamic_array &Dynamic_array::operator=(Dynamic_array & d) {					//-
	return *this;										//-
}												//-
												//-
Dynamic_array::~Dynamic_array() {								//-
}												//-
												//-
void Dynamic_array::print_state(void) {								//-
	cout << "size:" << size << endl;							//-
	for (Block * p = head_p; p != NULL; p = p->next_p) {					//-
		cout << "\tsize:" << p->size << " elements:";					//-
		for (int i = 0; i < p->size; i++) {						//-
			cout << p->a[i] << ' ';							//-
		}										//-
		cout << endl;									//-
	}											//-
}												//-
												//-
int Dynamic_array::get_size(void) {								//-
	return size;
}												//-
												//-
int& Dynamic_array::operator[](int i) {								//-
	// check i for range error								//-
	if (i < 0 || i >= size) {								//-
		throw Subscript_range_exception();						//-
	}											//-
												//-
	// find target block and index								//-
	Block_position position = find_block(i);						//-
												//-
	// return element at index i								//-
	return position.block_p->a[position.i];							//-
}												//-
												//-
void Dynamic_array::insert(int x, int i) {							//-
	// case 1: range error									//-
	if (i < 0 || i > size) {								//-
		throw Subscript_range_exception();						//-
	}											//-
												//-
	// case 2: empty array									//-
	if (size == 0) {									//-
		// create linked list consisting of a single new block				//-
		Block * new_block_p = new Block;						//-
		new_block_p->size = 1;								//-
		new_block_p->a[0] = x;								//-
		new_block_p->next_p = NULL;							//-
												//-
		// insert new block								//-
		insert_blocks(NULL, new_block_p);						//-
												//-
		// update total size								//-
		size++;										//-
												//-
		return;										//-
	}											//-
												//-
	// find target block and index								//-
	Block_position position = find_block(i);						//-
												//-
	// case 3: non-empty array; new block not needed					//-
	if (position.block_p->size < BLOCK_SIZE) {						//-
		// shift block array right							//-
		for (int j = position.block_p->size; j > position.i; j--) {			//-
			position.block_p->a[j] = position.block_p->a[j-1];			//-
		}										//-
												//-
		// assign x									//-
		position.block_p->a[position.i] = x;						//-
												//-
		// update array and block size							//-
		size++;										//-
		position.block_p->size++;							//-
												//-
	// case 4: non-empty array; new block needed						//-
	} else {										//-
		// create new block								//-
		Block * new_block_p = new Block;						//-
		new_block_p->size = 1;								//-
		new_block_p->next_p = NULL;							//-
												//-
		// case 4.a: insert x into old block						//-
		if (position.i < BLOCK_SIZE) {							//-
			// copy last array element to new block					//-
			new_block_p->a[0] = position.block_p->a[BLOCK_SIZE-1];			//-
												//-
			// shift old block array right						//-
			for (int j = position.block_p->size-1; j > position.i; j--) {		//-
				position.block_p->a[j] = position.block_p->a[j-1];		//-
			}									//-
												//-
			// assign x into old block						//-
			position.block_p->a[position.i] = x;					//-
												//-
		// case 4.b: insert x into new block						//-
		} else {									//-
			new_block_p->a[0] = x;							//-
		}										//-
												//-
		// update total size								//-
		size++;										//-
												//-
		// insert new block into linked list						//-
		insert_blocks(position.block_p, new_block_p);					//-
	}											//-
}												//-
												//-
void Dynamic_array::insert(Dynamic_array &p, int i) {						//-
	// case 1: range error									//-
    if (i < 0 || i > size) {
        throw Subscript_range_exception();
    }
	// case 2: parameter array empty							//-
    if(p.size==0)
        return;
    
	// case 3: array empty									//-
    if(size==0)
    {
        Block * copy_p = copy_blocks(p.head_p);
        insert_blocks(NULL,copy_p);
        size += copy_p->size;
        return;
    }

	// find target block and index								//-
	Block_position position = find_block(i);						//-
	// case 4: array non-empty; new blocks not needed					//-
    if (size % BLOCK_SIZE !=0 && p.size+(size%BLOCK_SIZE) <= BLOCK_SIZE) {
                for (int j = 0; j < p.size; j++)
        {
            position.block_p->a[i+j+p.size] = position.block_p->a[i+j];
            position.block_p->a[i+j] = p[j];
          
        }
    
    
        position.block_p->size += p.size;
        size += p.size;
        return;

    }
	// case 5: array non-empty; new blocks needed						//-
    else if((size%BLOCK_SIZE)+p.size>BLOCK_SIZE)
    {
        
		// copy p									//-
		Block * copy_p = copy_blocks(p.head_p);						//-
		// case 5.a: insert position at start of block					//-
        if(position.i%BLOCK_SIZE==0){
            insert_blocks(position.pre_block_p,copy_p);
            size+=p.size;
            return;
        }
		// case 5.b: insert position at middle of block					//-
        if(position.block_p->size - (i % BLOCK_SIZE) != 0){
            Block * split_block=new Block;
            split_block->size = position.block_p->size - (i % 5);
            for (int j = (i%BLOCK_SIZE); j <= BLOCK_SIZE; j++){
                split_block->a[j-(i%BLOCK_SIZE)] = position.block_p->a[j];
            }
            insert_blocks(position.block_p, copy_p);
            insert_blocks(copy_p, split_block);
            position.block_p->size -= i % BLOCK_SIZE;
            size += p.size;
            return;

            
        }
		// case 5.c: insert position after end of block					//-
        if(position.block_p->size - (i % BLOCK_SIZE) == 0){
            insert_blocks(position.block_p,copy_p);
            size+=p.size;
            return;
            
        }
		// update total size								//-
    }
}												//-
												//-
void Dynamic_array::remove(int i) {								//-
	// case 1: range error									//-
	if (i < 0 || i >= size) {
		throw Subscript_range_exception();
	}
	// find target block and index								//-
	Block_position position = find_block(i);
	// case 2: block size == 1								//-
	if (position.block_p->size == 1) {

		Block * pre_block_p = position.pre_block_p;
		Block * block_start_p = position.block_p;
		Block * block_end_p = position.block_p;
		remove_blocks(pre_block_p, block_start_p, block_end_p);
		size--;
	}
	// case 3: block size > 1								//-
	else if (position.block_p->size > 1) {
		// loop throughout all elements after i, replace element preceding them
		for (int j = i ; j < position.block_p->size; j++) {
			position.block_p->a[j] = position.block_p->a[j+1];
		};
		position.block_p->size--; // update block size
		size--; // update array size
	}
	// update total size									//-

}												//-
												//-
void Dynamic_array::remove(int start, int end) {						//-
    // case 1: range error
    if (start < 0 || end > get_size() || start>end) {
        throw Subscript_range_exception();
        return;
    }
    // case 2: empty array
    if(size==0){
        return;
    }
    // case 3:start and end are equal
    if(end-start==0)
        return;
    //case 4:start and end are in same block
    // find target blocks and index
    Block_position start_position=find_block(start);
    Block_position end_position=find_block(end);
    int start_ind = start % BLOCK_SIZE;
    int end_ind = end % BLOCK_SIZE;
    if(end_position.block_p==start_position.block_p){
    //4a takes out entire block
        if(start_ind==0 && end_ind==BLOCK_SIZE-1){
    //(Block * pre_start_p, Block * start_p, Block * end_p)
            remove_blocks(start_position.block_p,start_position.block_p,end_position.block_p);
        }
    //4b removes portion of a block
        else{
            for (int i = 0; i < BLOCK_SIZE - end_position.i; i++) {
                start_position.block_p->a[i + start_position.i] = start_position.block_p->a[i + end_position.i];
            }
            start_position.block_p->size -= (end_position.i - start_position.i);
        }
        size -= (end - start);
        return;
    }
    // case 5: start and end are in different blocks
    if (start_position.block_p != end_position.block_p){
        start_position.block_p->size=start_position.block_p->size - (BLOCK_SIZE - start_ind);
        //5a end block has at least an entire block after start block
        if(end_position.pre_block_p != start_position.block_p){
            remove_blocks(start_position.block_p,start_position.block_p->next_p, end_position.pre_block_p);
        }
        //5b end is mid block
        int moveFrom = 0;
        for(int moveTo = end_ind; moveTo<BLOCK_SIZE; moveTo++){
            end_position.block_p->a[moveFrom]=end_position.block_p->a[moveTo];
            moveFrom++;
        }
        end_position.block_p->size -= (end_ind);
        //5c start block is empty
        if(start_position.block_p->size==0){
            remove_blocks(start_position.pre_block_p,start_position.block_p,start_position.block_p);
            
        }
        //5d end block is empty
        if (end_position.block_p->size == 0){
            remove_blocks(end_position.pre_block_p,end_position.block_p,end_position.block_p);
        }
        size-=(end-start);
        return;
        
        
        
    }
 

}												//-
												//-
// ********** private functions **********							//-
												//-
// purpose											//-
//	return b where										//-
//		if i < size									//-
//			b.block_p->a[b.i] is the ith element overall				//-
//		else										//-
//			b.block_p->a[b.i-1] is the i-1st element overall			//-
//												//-
//		if b.block_p == head_p								//-
//			b.pre_block_p is NULL							//-
//		else										//-
//			b.pre_block_p points to block preceding b.block_p			//-
// preconditions										//-
//	i in [1..size]										//-
Dynamic_array::Block_position Dynamic_array::find_block(int i) {				//-
	Block_position position;								//-
												//-
	// scan Block list									//-
	position.i = i;										//-
	position.pre_block_p = NULL;								//-
	for (position.block_p = head_p;								//-
	position.block_p != NULL;								//-
	position.block_p = position.block_p->next_p) {						//-
		// found in current block							//-
		if (position.i < position.block_p->size) {					//-
			break;									//-
		}										//-
												//-
		// special case: insert just after last element					//-
		if (i == size && position.block_p->next_p == NULL) {				//-
			break;									//-
		}										//-
												//-
		// not found yet: advance							//-
		position.pre_block_p = position.block_p;					//-
		position.i -= position.block_p->size;						//-
	}											//-
												//-
	return position;									//-
}												//-
												//-
// purpose											//-
//	create a new linked list which is a copy of the list pointed to p			//-
//	return a pointer to the head of the new linked list					//-
// preconditions										//-
//	p is the head of a possibly empty linked list of blocks					//-
Dynamic_array::Block * Dynamic_array::copy_blocks(Block * p) {					//-
	Block * new_head_p = NULL;								//-
	Block * new_p;										//-
	while (p != NULL) {									//-
		// allocate and link in new block						//-
		if (new_head_p == NULL) {							//-
			new_p = new Block;							//-
			new_head_p = new_p;							//-
		} else {									//-
			new_p->next_p = new Block;						//-
			new_p = new_p->next_p;							//-
		}										//-
												//-
		// copy the elements								//-
		new_p->size = p->size;								//-
		for (int i = 0; i < p->size; i++) {						//-
			new_p->a[i] = p->a[i];							//-
		}										//-
												//-
		// advance									//-
		p = p->next_p;									//-
	}											//-
												//-
	// terminate new list									//-
	if (new_head_p != NULL) {								//-
		new_p->next_p = NULL;								//-
	}											//-
												//-
	return new_head_p;									//-
}												//-
												//-
// purpose											//-
//	insert the list headed by src_p into the list headed by head_p				//-
//	if dst_p is NULL									//-
//		insert the list at the start of the list headed by head_p			//-
//	else											//-
//		insert the list just after block dst_p						//-
// preconditions										//-
//	list headed by src_p is non-empty							//-
//	list headed by src_p has no blocks in common with the list headed by head_p		//-
void Dynamic_array::insert_blocks(Block * dst_p, Block * src_p) {				//-
	// find the last block in the list headed by src_p					//-
	Block * p = src_p;									//-
	while (p->next_p != NULL) {								//-
		p = p->next_p;									//-
	}											//-
												//-
	// insert at head									//-
	if (dst_p == NULL) { // insert at head							//-
		p->next_p = head_p;								//-
		head_p = src_p;									//-
												//-
	// insert after dst_p									//-
	} else { // insert after dst_p								//-
		p->next_p = dst_p->next_p;							//-
		dst_p->next_p = src_p;								//-
	}											//-
}												//-
												//-
// purpose											//-
//	remove the blocks pointed to by start_p and end_p, and all the blocks between		//-
// preconditions										//-
//	start_p and end_p point to blocks in the list headed by head_p				//-
//	end_p points to either the same block as start_p or a block to its right		//-
//	if start_p == head_p									//-
//		pre_start_p == NULL								//-
//	else											//-
//		pre_start_p points to the block immediately preceding start_p			//-
//												//-
void Dynamic_array::remove_blocks(Block * pre_start_p, Block * start_p, Block * end_p) {	//-
	// release the blocks									//-
	while (1) {										//-
		// release start_p								//-
		Block * p = start_p->next_p;							//-
		delete start_p;									//-
												//-
		// advance									//-
		if (start_p == end_p) {								//-
			break;									//-
		} else {									//-
			start_p = p;								//-
		}										//-
	}											//-
												//-
	// link left and right sublists								//-
	if (pre_start_p == NULL) {								//-
		head_p = end_p->next_p;								//-
	} else {										//-
		pre_start_p->next_p = start_p->next_p;						//-
	}											//-
}												//-
