// 0x6080604052
// 348015600e575f80fd5b5060a580601a5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea2646970667358221220181c72e94b7f6f28fa15c7ac7d5abe5c49f6d3330857ce237708b1c0de9434c364736f6c63430008190033

// 1. Contract creation code
// Free Memory Pointer
PUSH1	0x80  //[0x80]
PUSH1	0x40  //[0x40, 0x80]
MSTORE	      //[] //Memory 0x40 -> 0x80

// Otherwise, jump to continue execution
CALLVALUE       //[msg.sender]
DUP1	        //[msg.sender, msg.sender]
ISZERO	        //[msg.sender == 0, msg.sender]
PUSH1	0x0e    //[0x0e, msg.sender == 0, msg.sender]
JUMPI	        //[msg.value]
PUSH0	        //[0x00, msg.value]
DUP1	        //[0x00, 0x00, msg.value]
REVERT	        //[msg.value]

// Jump dest if msg.value == 0
// Sticks the runtime code on chain
JUMPDEST	        //[msg.value]
POP	                //[]
PUSH1	0xa5        //[0xa5]
DUP1	            //[0xa5,0xa5]
PUSH1	0x1a        //[0x1a, 0xa5, 0xa5]
PUSH0	            //[0x00, 0x1a, 0xa5, 0xa5]
CODECOPY	        //[0xa5]            Memory:[runtime code]
PUSH0	            //[0x00, 0xa5]
RETURN	            //[]
INVALID	            //[]

// 2. Runtime code
// Entry point for all calls
// free memory pointer
PUSH1	0x80
PUSH1	0x40
MSTORE	

// Checking for msg.value, and if given reverting
CALLVALUE	        //[msg.sender]
DUP1	            //[msg.sender, msg.sender]
ISZERO	            //[msg.sender == 0, msg.sender]
PUSH1	0x0e        //[0x0e, msg.sender == 0, msg.sender]
JUMPI	            //[msg.value]
//Jump to "continue!" if msg.value == 0

// Revert if msg.value has value
PUSH0	            //[0x00, msg.value]
DUP1	            //[0x00, 0x00, msg.value]
REVERT	            //[msg.value]

// We check the calldata to see if it's big enough for a function selector. 
// We jump to a revert if its too small
// if msg.value == 0, start here
JUMPDEST	        //[msg.value]
POP	                //[]
PUSH1	0x04        //[0x04]
CALLDATASIZE	    // [calldatasize, 0x04]
LT	                // [calldatasize < 0x04]
PUSH1	0x30        // [0x30, calldatasize < 0x04]
JUMPI	            //[]
// if calldata_size < 0x04 -> calldata_jump

// Function dispatching in solidity!
PUSH0	            //[0x00]
CALLDATALOAD	    //[32bytes of calldata]
PUSH1	0xe0        //[0xe0, 32bytes of calldata]
SHR	                //[calldata[0:4]] //func_selector

// Function dispatching in setNumberOfHorses!
DUP1	            //[func_selector, func_selector]
PUSH4	0xcdfead2e  //[0xcdfead2e, func_selector, func_selector]
EQ	                //[func_selector == 0xcdfead2e, func_selector]
PUSH1	0x34        //[0x34, func_selector == 0xcdfead2e, func_selector]
JUMPI	            //[func_selector]
// if func_selector == 0xcdfead2e -> set_number_of_horses

// Function dispatching in readNumberOfHorses!
DUP1	            //[func_selector, func_selector]
PUSH4	0xe026c017  //[0xe026c017, func_selector, func_selector]
EQ	                //[func_selector == 0xe026c017, func_selector]
PUSH1	0x45        //[0x45, func_selector == 0xe026c017, func_selector]
JUMPI	            //[func_selector]
// if func_selector == 0xe026c017 -> get_number_of_horses


// calldata_jump
// Revert jumpset
JUMPDEST	        //[]
PUSH0	            //[0]
DUP1	            //[0, 0]
REVERT	            //[]

// updateHorseNumber jump dest 1
JUMPDEST	        //[func_selector]
PUSH1	0x43        //[0x43, func_selector]
PUSH1	0x3f        //[0x3f, 0x43, func_selector]
CALLDATASIZE	    //[calldatasize, 0x3f, 0x43, func_selector]
PUSH1	0x04        //[0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH1	0x59        //[0x59, 0x04, calldatasize, 0x3f, 0x43, func_selector]
JUMP	            //[0x04, calldatasize, 0x3f, 0x43, func_selector]

// jump dest 4
// we can finally run an sstore to save our value to storage
JUMPDEST	        //[calldata (of number to update), 0x43, func_selector]
PUSH0	            //[0x00, calldata (of number to update), 0x43, func_selector]
SSTORE	            //[0x43, func_selector]
JUMP	            //[func_selector]
// Jump dest 5

// Jump dest 5
JUMPDEST	        //[func_selector]
STOP	            //[func_selector]


// read numberOfHorses jump dest 1
// the only read number of horses dest
JUMPDEST	        //[func_selector]
PUSH0	            //[0x00, func_selector]
SLOAD	            //[numHorses, func_selector]
PUSH1	0x40        //[0x40, numHorses, func_selector]
MLOAD	            //[0x80, numHorses, func_selector] //Mrmory [0x40: 0x80] (free memory pointer)
SWAP1	            //[numHorses, 0x80, func_selector]
DUP2	            //[0x80, numHorses, 0x80, func_selector]
MSTORE	            //[0x80, func_selector]  Memory: 0x80: numHorses
PUSH1	0x20        //[0x20, 0x80, func_selector]
ADD	                //[0xa0, func_selector]
PUSH1	0x40        //[0x40, 0xa0, func_selector]
MLOAD	            //[0x80, 0xa0, func_selector]
DUP1	            //[0x80, 0x80, 0xa0, func_selector]
SWAP2	            //[0xa0, 0x80, 0x80, func_selector]
SUB	                //[0xa0 - 0x80, 0x80, func_selector]
SWAP1	            //[0x80, 0xa0 - 0x80, func_selector]
// Return a value of size 32 bytes, thts located at position 0x80 in memory
RETURN	            //[func_selector]

// updateHorseNumber jump dest 2
// check to see if there is a value to update the value to
// 4 bytes for function selector, 32 bytes for horse number
JUMPDEST	            //[0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH0	                //[0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH1	0x20            //[0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
DUP3	                //[0x04, 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
DUP5	                //[calldatasize, 0x04, 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]      
SUB	                    //[calldatasize - 0x04, 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
SLT	                    //[calldatasize - 0x04 < 0x20, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
ISZERO	                //[calldatasize - 0x04 < 0x20 == true, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
PUSH1	0x68            //[0x68, calldatasize - 0x04 < 0x20 == true, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
JUMPI	                //[0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
// We are going to jump dest 3 if there is more calldata than:
// function selector + 0x20

// Revert if there isnt enough calldata
PUSH0	                //[0x00, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
DUP1	                //[0x00, 0x00, 0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
REVERT	                //[0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]


// updateHorseNumber jump dest 3
// Grab the calldata for updating the horse
// Delete somestuff in the stack
JUMPDEST	            //[0x00, 0x04, calldatasize, 0x3f, 0x43, func_selector]
POP	                    //[0x04, calldatasize, 0x3f, 0x43, func_selector]
CALLDATALOAD	        //[calldata (of number to update), calldatasize, 0x3f, 0x43, func_selector]
SWAP2	                //[0x3f, calldatasize, calldata (of number to update), 0x3f, 0x43, func_selector]
SWAP1	                //[calldatasize, 0x3f, calldata (of number to update), 0x3f, 0x43, func_selector]
POP	                    //[0x3f, calldata (of number to update), 0x43, func_selector]
JUMP	                //[calldata (of number to update), 0x43, func_selector]
// jump to jump dest 4

// 3. Metadata
INVALID	
LOG2	
PUSH5	6970667358
INVALID	
SLT	
KECCAK256	
XOR	
SHR	
PUSH19	e94b7f6f28fa15c7ac7d5abe5c49f6d3330857
INVALID	
INVALID