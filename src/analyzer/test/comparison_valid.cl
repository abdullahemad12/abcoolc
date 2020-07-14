class Main {
	x : Int <- 0;
	y : Int <- 20; 
	main() : Bool {
		{
			~x;
			x <= 3;
			y < x;	
			x = y;
			not (x = y);
		}
	};


};
