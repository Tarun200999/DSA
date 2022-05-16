class NumArray {
    vector<int> segment;
    vector<int> nums;
    int size;
 public:
    void update(int seg,int index,int value,int low,int high)
    {
       int mid=low+(high-low)/2;
       if(low==high && index==low) {
           segment[seg]=value;
           return;
        }
       else if(index<=mid)
       {
            update(2*seg+1,index,value,low,mid);
       }
        else{
            update(2*seg+2,index,value,mid+1,high);
        }
    segment[seg]=segment[2*seg+1]+segment[2*seg+2];
    }

    int solve(int index,int left,int right,int low,int high)
    {
        //  IF SEGMENT IS COMPLETY IN QUERY RANGE 
        
        if(low>=left && high<=right) return segment[index];
        else if(left>high || right<low)
        {
            //IF SEGENT IS COMLETY OUTSIDE
            return 0;
        }
        else{
            // SOME OVERLAP
            int mid=low+(high-low)/2;
            int leftAns=solve(2*index+1,left,right,low,mid);
            int rightAns=solve(2*index+2,left,right,mid+1,high);
            
            return leftAns+rightAns;
        }
    }
     void buildSegmentTree(int index,int low,int high,vector<int> &nums)
     {
         if(low==high)
         {
            segment[index]=nums[low];
            return;
         }
        
         int mid = low + (high-low)/2;
        
         buildSegmentTree(2*index+1,low,mid,nums);  
        
         buildSegmentTree(2*index+2,mid+1,high,nums);
        
         segment[index]=segment[2*index+1]+segment[2*index+2];
                
     }
    NumArray(vector<int>& input) {
        
        size=input.size();
        
        nums=input;
        
        segment.resize(4*size+1);
        
        buildSegmentTree(0,0,size-1,nums);
    }
    
    void update(int index, int val) {
    
        update(0,index,val,0,size-1);
    }
    
    int sumRange(int left, int right) {
        return solve(0,left,right,0,size-1);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */
