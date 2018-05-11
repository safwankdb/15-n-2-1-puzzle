#include<bits/stdc++.h>
using namespace std;

int goalVector[10][10];
int n;
struct node
{
	int v[10][10];
	int h=0,g=0;
	string path="";
	//node * parent=nullptr;
	node & operator = (const node & b)
	{
		this->h=b.h;
		this->g=b.g;
		this->path=b.path;
		for (int i=0;i<n;++i)
		{
			for (int j=0;j<n;++j)
			{
				this->v[i][j]=b.v[i][j];
			}
		}
		return(*this);
	}
};

node goal;
int mDist(node cNode)
{
    int M_d = 0;
    for(int i1=0; i1<n; i1++)
    {
        for(int j1=0; j1<n; j1++)
        {
            if(i1==n-1&&j1==n-1)
                break;
            for(int i2=0;i2<n;i2++)
            {
                for(int j2=0;j2<n;j2++)
                {
                    if(goalVector[i1][j1]==cNode.v[i2][j2])
                        M_d = M_d + abs(i1-i2) + abs(j1-j2);
                }
            }
        }
    }
    return M_d;
}
bool operator<(node a, node b)
{
	return a.h+a.g<b.h+b.g;
}
bool operator==(const node & a, const node & b)
{
	if(a.h!=b.h)
		return false;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(a.v[i][j]!=b.v[i][j])
				return false;
	return true;
}
vector<node> openList,closedList;
node up(node cNode)
{
    node ans = cNode;
    //ans.parent=&cNode;
	ans.g=cNode.g+1;
	ans.h=mDist(ans);
    int x,y;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(ans.v[i][j] == 0)
            {
                x=i;
                y=j;
            }
    //ans.cMove='U';
    if(x==0)
    {
    	//ans.h=10000;
    	return ans;
    }
    ans.v[x][y]=cNode.v[x-1][y];
    ans.v[x-1][y]=0;
    ans.path+='U';
    //moves.push_back('U');
    ans.h=mDist(ans);
    return ans;
}
node down(node cNode)
{
    node ans=cNode;
    //ans.parent=&cNode;
	ans.g=cNode.g+1;
	ans.h=mDist(ans);
    int x,y;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(ans.v[i][j] == 0)
            {
                x=i;
                y=j;
            }
    //ans.cMove='D';
    if(x==n-1)
    {
    	//ans.h=10000;
        return ans;
    }
    ans.v[x][y]=cNode.v[x+1][y];
    ans.v[x+1][y]=0;
    //moves.push_back('D');
    ans.h=mDist(ans);
    ans.path+='D';
    return ans;
}
node left(node cNode)
{
    node ans=cNode;
    //ans.parent=&cNode;
	ans.g=cNode.g+1;
	ans.h=mDist(ans);
    int x,y;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(ans.v[i][j] == 0)
            {
                x=i;
                y=j;
            }
    //ans.cMove='L';
    if(y==0)
    {
    	//ans.h=10000;
        return ans;
    }
    ans.v[x][y]=cNode.v[x][y-1];
    ans.v[x][y-1]=0;
    //moves.push_back('L');
    ans.h=mDist(ans);
    ans.path+='L';
    return ans;
}
node right(node cNode)
{
    node ans=cNode;
    //ans.parent=&cNode;
	ans.g=cNode.g+1;
	ans.h=mDist(ans);
    int x,y;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(ans.v[i][j] == 0)
            {
                x=i;
                y=j;
            }
    //ans.cMove='R';
    if(y==n-1)
    {
    	//ans.h=10000;
        return ans;
    }
    ans.v[x][y]=cNode.v[x][y+1];
    ans.v[x][y+1]=0;
    //moves.push_back('R');
    ans.h=mDist(ans);
    ans.path+='R';
    return ans;
}
void print(node p)
{
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout<<p.v[i][j]<<' ';
		}
		cout<<endl;
	}
}
int findIndex(node a, vector<node> v)
{
	int k=0;
	bool flag=false;
	for (int i = 0; i < v.size(); ++i)
	{
		if(v[i]==a)
		{
			k=i;
			flag=true;
			break;
		}
	}
	if(flag)
		return k;
	return -1;
}
bool find(node a, vector<node> v)
{
	if(findIndex(a,v)>=0)
		return 1;
	return 0;
}

void aStar()
{
	while(openList.size()>0)
	{
		vector<node>::iterator min=min_element(openList.begin(),openList.end());
		node process=*min;
		
		if(process==goal||process.h==0)
		{
			//cout<<"DONE"<<endl;
			cout<<process.path<<endl;
			return;
		}
		openList.erase(min);
		closedList.push_back(process);
		node temp[4];
		temp[0]=up(process);
		temp[1]=right(process);
		temp[2]=down(process);
		temp[3]=left(process);
		
		//cout<<openList.size()<<endl;
		
		//node temp;
		
		for(int i=0;i<4;i++)
		{
			if(find(temp[i],closedList))
	        {
				continue;
			}
			//print(temp[i]);
			if(!find(temp[i],openList))
			{
				openList.push_back(temp[i]);
			}
			//print(temp);
			else
			{
   				//print(temp[i]);
				node actualNode=openList[findIndex(temp[i],openList)];
				if(temp[i].g<actualNode.g)
				{
					actualNode=temp[i];
				}
			}
		}
	}
	cout<<"Not possible to reach goal"<<endl;
}
int main()
{
	cin>>n;
	for(int i=0;i<n;i++)
	{
		//cout<<i<<endl;
		for(int j=0;j<n;j++)
		{
			goalVector[i][j]=(n*i+j+1)%(n*n);
		}
	}
	node goal;
	for (int i=0;i<n;++i)
	{
		for (int j=0;j<n;++j)
		{
			goal.v[i][j]=goalVector[i][j];
		}
	}
	node input;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{
			cin>>input.v[i][j];
		}
	input.g=0;
	//input.parent=&input;
	input.h=mDist(input);
	openList.push_back(input);
	//print(goal);
	//cout<< (input==goal)<<endl;
	aStar();
}
