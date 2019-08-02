1. The C source file framework

The first section is the copyright notice at the beginning of each .c and .h file

/*******************************************************************************
 * LEGALESE:   Copyright (c) 2018, LightWAN Corporation.
 *
 * This source code is confidential, proprietary, and contains trade
 * secrets that are the sole property of LightWAN Corporation.
 * Copy and/or distribution of this source code or disassembly or reverse
 * engineering of the resultant object code are strictly forbidden without
 * the written consent of LightWAN Corporation LLC.
 *
 *******************************************************************************
 * FILE NAME :      ***
 *
 * DESCRIPTION :    ***
 *
 * AUTHOR :         ***
 * 
 * HISTORY :        ***     MM/DD/YYYY  create
 ******************************************************************************/

The second section consists of preprocessor directives (#include and #define),
followed by declarations of external, global, and static variables.

#include "<file1>.h"
#include "<file2>.h"

#define <name1> <value>                 /* one line description        */
#define <name2> <value>                 /* one line description        */

extern <type> <name1>;                  /* one line description        */
extern <type> <name2>;                  /* one line description        */

static <type> <name3> = <value>;        /* one line description        */

* in header file example.h, add

#ifndef _EXAMPLE_H_
#define _EXAMPLE_H_
body
#endif

2. Comments

In general, the comments SHOULD be neat and clean.

Comments before each function

/*******************************************************************************
 * NAME:  name of function
 *
 * DESCRIPTION:
 *      description of function
 *
 * INPUTS:
 *      variable name: description
 * RETURN:
 *      description to return value, for example
 *      SUCCESS         1
 *      FAILURE         0
 */

Comments before each major functional block

/*******************************************************************************
 * Brief description or name of the functional block
 ******************************************************************************/

Comments before some functional block (at lease several lines of code)

/*
 * Description.
 */

One line comments, commenting just one line of code

one line code       /* one line description        */

3. Formating

3.1 Source files must not include any <TAB> characters.
3.2 Source files must not include any non-printable characters such as <CTRL-L> and
    <CTRL-Z>.
3.3 The following command can be used to properly indent a C source file, and remove
    MS-DOS <CR> and <EOF> characters and <TAB> characters:

    mv foo.c foo.bak ; dos2unix -c ascii foo.bak; \
    indent < foo.bak | expand -4 > foo.c ; rm foo.bak

    When use some edit tools, save as unix format. For example, source insight has option
    to configure to save unix format.

    Recommended source code editor: source insight.

3.4 Indent 4 spaces when needed

    If you use VIM as your editor, the following lines should be added to your ".vimrc"
    file. You can find these and many more configuration options in "/home/lsun/.vimrc"

    Expand tabs
    set expandtab

	Set tab stops
	set ts=4

	Number of spaces to use for (auto)indent step
	set shiftwidth=4

	For visual studio, Tools -> options -> tabs -> choose "tab size" and "indent size"
	of 4 and mark "Insert spaces"

3.5 For branching, while, and switch etc, bracket start in the next line, for example:

	if (x > y)
	{
		a = b;
	}
	else
	{
		a = c;
	}

3.6 Max line length 120

3.7 in function declaraction/definition, put each function argument in a single line
	see the LW_FooBar example.

    if the function doesnt take any argument, use the following:

    LW_PacketWrapper*
    LW_GetPacketFromInputQueue(
        void
        )

3.8 Try to call function in one line, if the line is too long, or you wish to add comments to the arguments,
	also put arguments on different lines:

        ok = LW_FooBar(
            NULL,     /* no real device associated */
            ParameterArray,
            ARRAYSIZE(ParameterArray),
            &DevInfo
            );

4. Naming conventions

First define two naming styles:

Pascal style: Capitalize the 1st character of each word, for example, GetSystemTimeAsFileTime.

Camel style:  Lower the 1st charactor of the name, but capitalize the 1st character of each
              succeding word, for example, getSystemTimeAsFileTime.

4.1 File names: use Camel Style.

4.1.1	For platform independent:
		lightwan[Engine | Core][Comp | Tcp | Pic | Video ]Xxx.[ c | h ]

		[] means choose either one or not choose any one.

4.1.2	For platform dependent:
		[ce|linux|vxw][CBase | EBase]Xxx.[c | h ]

4.2	Function:
    - function names use LW_ prefix plus Pascal style name,
      for example: LW_GetSystemTimeAsFileTime()
    - function arguments use Pascal style

    LW_[CE|VXW|LINUX][Core | Engine | C | E | CBase | EBase][Comp | Tcp | Pic | Video]Xxx

    The last string reflects what the function does.

    In case the function is some platform private (in /private directory and the function
    can only be used in base code), one of the platform label ([CE|VXW|LINUX]) must be added.

    Regarding [Core | Engine | C | E | CBase | EBase]

    In Core/Engine, if the function is used by base, use Core | Engine, otherwise use C | E
    In base code, use CBase | EBase

4.3 Local variables use Camel stype.

4.4 struct/union/enum:

    struct/union/enum tag names use a leading "_" followed by all capital separated by "_".
    the typedef's name removes the leading "_" in the tag name, as shown in the following example.

    enum members use all uppercase separated by "_":

            typedef enum _LW_HANDSHAKE_STATE
            {
                LW_HANDSHAKE_STATE_INITIAL,
                LW_HANDSHAKE_STATE_FINISHED
            }
            LW_HANDSHAKE_STATE;

    struct/union members use Pascal names.

            typedef struct _PACKET_CONTEXT
            {
                 uint32_t SrcAddr;
                 uint32_t DstAddr;
            }
            PACKET_CONTEXT;

4.4.1	For platform independent
		LW_[CORE | ENGINE]_[COMP | TCP | PIC | VIDEO ]_XXX
		in core/include or engine/include

		In case it is not specific for core or engine, do not use CORE | ENGINE,
		same for feature options COMP | TCP | PIC | VIDEO

4.4.2	For platform dependent
		LW_[CE|VXW|LINUX]_[COMP | TCP | PIC | VIDEO ]_XXX
		in cbase/include or ebase/include

4.5 global variables start with g_ + Pascal style. such as g_KernelInputQueue.
4.6 static variables start with s_ + Pascal style. such as s_Lock.
4.7 All symbolic constants (#defines) MUST be upper case, with underscore characters used
	to delimit words. It is required to start with LW_, For example:
	#define LW_HASH_TABLE_SIZE 1024
4.8 const global or static variables that serves similar as a macro uses all uppercase separated "_":
	It is requried to start with LW_, for example:
	static uint32_t const LW_RETRY_COUNT = 5;
4.9 Include <stdint.h>, use its variable type.

5	check return values of **ALL** function calls that has a return value. if we really don't 
	care the return value of a particular function calls, "(void)" should be used to cast the 
	function return. if we are 101% sure that the function should NOT return failure, ASSERT 
	should be used.

	e.g.:       (void)fclose(fp);    /* we dont care. it should succeed. 
	                                  * even if it fails we have no good 
                                      * ways to handle the error. */ 

	e.g.:       decodeStatus = JPEGDecode(anAbsolutelyValidJPEGBuffer); 
                LW_ASSERT(LW_SUCCEEDED(decodeStatus)); 

5.1 in many existing APIs, the cleanup/finalize functions return a value indicating whether 
	it succeeded or not. in too many scenarios these return values means nothing to us. we 
	have no good way to handle those errors anyways, like in the example above. these functions
	should usually be prefixed '(void)' when called. 
	such as: (void)CloseHandle(...); 
	(void)LW_EngineUninit(...).

5.2 when we design APIs that may fail, we should return LW_STATUS. do *NOT* take the
	traditional CRT/WIN32 approaches by return a TRUE/FALSE and update a global error code
	variable like 'errno'. the traditional way has MANY disadvantages and is a very bad 
	coding practice.

6	use LW_ASSERT for all important assumptions. 
6.1 LW_ASSERT pointer function parameters that must NOT be NULL. 
6.2 LW_ASSERT values that should be within a certain range. 
6.3 LW_ASSERT function return values in certain cases like the above. 

7	watch for integer overflow. in the picture/video code there will be lots of computations like
	numOfPixels = width * height. if these values are obtained from data stream/files, they are 
	the easy targets for integer/buffer overrun attack. under such circumstance *ALL* integer 
	operations *MUST* guard against overflow attack.

7.1 to detect integer add overflow:  if (a + b < a) then overflow. 
7.2 to detect multiplication overflow: if ((ULONG)-1 / b > a) then overflow. 
7.3 if an internal function takes a parameter that is guaranteed to be within a certain range 
	(so we dont have to add validation to decrease the performance), the parameter MUST be LW_ASSERT'd.

8	one function should have only a single return at the end. if there are error cases use the 
	function-call --> failure-check --> function-call --> failure-check --> ... sequence. 
	like the following:

    LW_STATUS foo(void) 
    { 
        void* ptrA = NULL; 
        LW_STATUS status = LW_STATUS_OK; 
        .... 
        ptrA = malloc(sizeA); 
        if (ptrA == NULL) 
        { 
            status = LW_STATUS_OUTOFMEMORY; 
            goto CommonReturn; 
        } 
        .... 
    CommonReturn: 
        .... 
        if (ptrA != NULL) 
        { 
            free(ptrA); 
        } 
        return status; 
    } 

8.1 'goto' is NOT evil if used properly. our rule is, there can only be AT MOST ONE label 
	(for goto) near the end of the function for cleanup purposes.

8.2 if there are resources to be acquired, the variables (such as ptrA above) MUST be declared
	and initialized to NULL at the beginning of the function.

8.3 the return value variable (status) MUST be declared and initialized at the beginning of the function. 

	This code structure is the best for logic understanding and code maintenance.

9	Other rules

9.1 Warning free

9.2 do NOT use overly-deep nested if and loops. suggest no more than 4 levels. 

9.3 do NOT use magic numbers/strings directly in the code unless they are standard defined. 
	even if they are standards, it is still preferable to use constants or macros.

9.4 use static functions if they are not meant to be called by anywhere outside the c file. 
  
9.5 use 'const' pointer if the buffer is not supposed to be altered in the function. 

	9.4 and 9.5 helps both code understanding and compiler optimizations.

9.6 Performance consideration

	Try LW_INLINE or LW_FORCE_INLINE if the function is on data path.

9.7	watch for buffer overflow. all functions taking a buffer as parameter MUST take the buffer
	length as a parameter. do NOT use the traditional string functions like strcpy(), 
	strcat(), etc. i suggest using memcpy() instead.

9.8 SAL annotations

    It is required to follow SAL annotations

    http://msdn2.microsoft.com/en-us/library/ms235402(VS.80).aspx

    SAL annotation not only allows msft's source scan tools (prefast/prefix) to locate the code
    bug such as bad parameters and buffer overflow, etc easily at compile time. it also helps
    the code readers / developers to very quickly understand the details of what parameters to
    pass in a functions. e.g.:

    __success(return)
    BOOL
    LW_FooBar(
        __in_opt HANDLE DeviceHandle,
        __in_ecount(NumElements) uint32_t const* UInt32Array,
        __in size_t NumElements,
        __deref_out LW_DEVICE_INFO** DevInfo
        );

    from this the developer can see that:

        1) DeviceHandle is a handle to pass in, and it can be NULL.
        2) UInt32Array is an array of uint32_t to pass in. the array has NumElements elements.
           and the pointer can NOT be NULL.
        3) on a successfully return from the function, it will allocate a data structure,
           initialize it and pass the pointer out thru DevInfo.
        4) return true indicates a success. otherwise it is failure and the content in DevInfo
           is not defined.

    SAL annotations defines lots of details that cannot be expressed by C/C++ syntax and it
    helps development a lot.
