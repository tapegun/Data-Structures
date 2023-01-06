/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 * stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 *
 * **Hint**: think recursively!
 *
 * @note You may modify the stack as long as you restore it to its original
 * values.
 *
 * @note You may use only two local variables of type T in your function.
 * Note that this function is templatized on the stack's type, so stacks of
 * objects overloading the + operator can be summed.
 *
 * @note We are using the Standard Template Library (STL) stack in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param s A stack holding values to sum.
 * @return  The sum of all the elements in the stack, leaving the original
 *          stack in the same state (unchanged).
 */
template <typename T>
T sum(stack<T>& s)
{
    if(s.empty()){
        return T();
    }

    T first = s.top();
    //stack<T> tempStack = s
    s.pop();
    // Your code here
    T soln = first + sum(s);
    s.push(first);
    return soln; // stub return value (0 for primitive types). Change this!
                // Note: T() is the default value for objects, and 0 for
                // primitive types
}

/**
 * Checks whether the given string (stored in a queue) has balanced brackets.
 * A string will consist of square bracket characters, [, ], and other
 * characters. This function will return true if and only if the square bracket
 * characters in the given string are balanced. For this to be true, all
 * brackets must be matched up correctly, with no extra, hanging, or unmatched
 * brackets. For example, the string "[hello][]" is balanced, "[[][[]a]]" is
 * balanced, "[]]" is unbalanced, "][" is unbalanced, and "))))[cs225]" is
 * balanced.
 *
 * For this function, you may only create a single local variable of type
 * `stack<char>`! No other stack or queue local objects may be declared. Note
 * that you may still declare and use other local variables of primitive types.
 *
 * @param input The queue representation of a string to check for balanced brackets in
 * @return      Whether the input string had balanced brackets
 */
bool isBalanced(queue<char> input)
{

    // @TODO: Make less optimistic
    stack<char> temp; 
    while(!input.empty()){
        if(input.front() == '['){
            temp.push(input.front());
            input.pop();
            break;
        }
        else if(input.front() == ']'){
            return false;
        }
        else if(input.front()!= '['){
            input.pop();
        }
    }
    while(!input.empty()){
        if(input.front() == ']' && temp.empty()){
            return false;
        }
        else if(input.front()==']' && temp.top() == '['){
            input.pop();
            temp.pop();

        }
        else if(input.front() != '['){
            input.pop();
        }
        else {
            temp.push(input.front());
            input.pop();
        }
    }

    return (temp.empty());
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 *
 * **Hint**: You'll want to make a local stack variable.
 *
 * @note Any "leftover" numbers should be handled as if their block was
 * complete.
 *
 * @note We are using the Standard Template Library (STL) queue in this
 * problem. Its pop function works a bit differently from the stack we
 * built. Try searching for "stl stack" to learn how to use it.
 *
 * @param q A queue of items to be scrambled
 */
template <typename T>
void scramble(queue<T>& q)
{
    queue<T> tempSol;
    stack<T> s;
    int start = 0;
    int num = 1;
    while(!q.empty()){
        //std::cout<<q.size()<< " " << q.front()<< " "<< num<<std::endl;
    
        if((q.size() < unsigned(num)) && start == 0){
            while(!q.empty()){
                //if(!s.empty()){std::cout<<s.top()<<std::endl;}
                //std::cout<< s.empty() <<std::endl;
                //while(!s.empty()){s.pop();}
                if(num%2 == 0){
                    //std::cout<<"even ending: " <<q.front() <<std::endl;
                    s.push(q.front());
                    q.pop();
                }
                if(num%2 == 1){
                    //std::cout<<"odd ending: " <<q.front() <<std::endl;
                    tempSol.push(q.front());
                    q.pop();
                }
            }
            if(num%2 == 0){
                //std::cout<<"odd evenending 2: " <<q.front() <<std::endl;
                while(!s.empty()){
                    tempSol.push(s.top());
                    s.pop();
                }
            }
            break;

        }
        if(start == num && num%2 == 0){
            //std::cout<< "end evem: "<<q.front() <<std::endl;
            while(!s.empty()){
                tempSol.push(s.top());
                s.pop();
            }
            num++;
            start = 0;
            continue;
        }
        if(start == num && num%2 == 1){
            //std::cout<<"end odd: " <<q.front() <<std::endl;
            num++;
            start = 0;
            continue;
        }
        if(num%2 == 0){
            //std::cout<<"even : " <<q.front() <<std::endl;
            s.push(q.front());
            q.pop();
            start++;
            continue;
        }
        if(num%2 == 1){
            //std::cout<<"odd: " <<q.front() <<std::endl;
            tempSol.push(q.front());
            q.pop();
            start++;
            continue;
        }
        
    }
    

    q.swap(tempSol);

    // optional: queue<T> q2;

    // Your code here
}
}
