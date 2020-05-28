(*
 * This program creates a stack which is then used for an interpreter of the defined language.
 * Author - Abdullah Emad
 * Compilation - coolc stack.cl atoi.cl
 * Execution - spim stack.s
 *)
class Main inherits IO{
	list : List;
	handleQueries() : Object{
		let 	output : Object <- self.out_string(">"),
			input : String <- self.in_string()
			in
				if(input = "+") then 
				{
					list.insertPlus();
					handleQueries();
				}
				else if(input = "s") then 
				{
					list.insertSwap();
					handleQueries();
				}
				else if(input = "e") then
				{
					list.evaluate();
					handleQueries();
				}
				else if(input = "d") then
				{
					list.display();
					handleQueries();
				}					
				else if(input = "x") then
				{
					self;
				}
				else 
				{
					list.insertInt((new A2I).a2i(input));
					handleQueries();	
				}
				fi fi fi fi fi
	};
	main():Object{
		{
			list <- (new List).init();
			handleQueries();
		}
	};
};

class Node {
	next: Node;
	init(n : Node) : Node { 
		{
			next <- n;
			self;
		}	
	};
	getNext() : Node {
		next
	};
	setNext(n : Node) : Node {
		next <- n
	};	
};

class IntNode inherits Node {
	item : Int;
	initC(i : Int, node : Node) : IntNode {
		{
			init(node);
			item <- i;
			self;
		}
	};
	getItem() : Int {
		item
	};
};

class PlusNode inherits Node {

};
 
class SwapNode inherits Node {

}; 

class List {
	head : Node; 
	nil : Node;
	init() : List {
		self
	};
	
	insertInt(i : Int) : Object {
		head <- (new IntNode).initC(i, head)
	};
	insertPlus() :  Object {
		head <- (new PlusNode).init(head)
	};

	insertSwap() : Object {
		head <- (new SwapNode).init(head)
	};
	evaluatePlus() : Object {
		let first : IntNode <- 
			case head.getNext() of 
				n : IntNode => n;
				o : Node => (new IntNode).initC(0, nil);
			esac,
		    second : IntNode <-
			case first.getNext() of 
				n : IntNode => n; 
				o : Node => (new IntNode).initC(0, nil);
			esac,
		    sum : Int <- first.getItem() + second.getItem()
		in 
		    head <- (new IntNode).initC(sum, second.getNext())
	
	};
	evaluateSwap() : Object {
		let first : Node <- head.getNext(),
		    second : Node <- first.getNext()
		in
		    {
			first.setNext(second.getNext());
			second.setNext(first);	
			head <- second;
		    }
	};
	
	evaluate() : Object {
		{
		    if(IsVoid head) then self
		    else 
			    case head of
				    pNode : PlusNode => evaluatePlus();
				    sNode : SwapNode => evaluateSwap(); 
				    iNode : IntNode => self;
			    esac
			fi;
		}	
	};

	display() : Object {
		displayHelper(head)
	};
	displayHelper(node : Node) : Object {
		if(IsVoid node) then self
		else 
			let str : String <- 
				case node of 
					pNode : PlusNode => "+";
					sNode : SwapNode => "s";
					iNode : IntNode => (new A2I).i2a(iNode.getItem());
				esac
			in 
				{
					(new IO).out_string(str.concat("\n"));
					displayHelper(node.getNext());
				}
		fi 
	};	
};
