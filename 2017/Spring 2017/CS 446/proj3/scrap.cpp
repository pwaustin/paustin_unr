		else if ( line == "System memory (kbytes)" )
			{

			fin >> systemMemory;

			if ( systemMemory <= 0 )
				{
				fin.close();
				throw "Error: invalid value for system memory, aborting.";
				return;
				}

			}

		else if ( line == "System memory (Mbytes)" )
			{

			fin >> systemMemory;

			systemMemory *= 1000;

			if ( systemMemory <= 0 )
				{
				fin.close();
				throw "Error: invalid value for system memory, aborting.";
				return;
				}

			}

		else if ( line == "System memory (Gbytes)" )
			{

			fin >> systemMemory;

			systemMemory *= 1000000;

			if ( systemMemory <= 0 )
				{
				fin.close();
				throw "Error: invalid value for system memory, aborting.";
				return;
				}
