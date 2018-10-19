	for ( int i = 0; i < eventSequence.size(); i++ )
		{

		//handle S code events

		if ( eventSequence[i].getCode() == 'S' && eventSequence[i].getDescriptor() == "start" )
			{

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::	for ( int i = 0; i < eventSequence.size(); i++ )
		{

		//handle S code events

		if ( eventSequence[i].getCode() == 'S' && eventSequence[i].getDescriptor() == "start" )
			{

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
				" - Simulator program starting" << endl; 

			stateManager.setState(0); //initialize PCB with start state

			}

		else if ( eventSequence[i].getCode() == 'S' && eventSequence[i].getDescriptor() == "end" )
			{

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0  << 
				" - Simulator program ending" << endl; 

			stateManager.setState(4); //set PCB to exit state

			}

		//handle A code events

		else if ( eventSequence[i].getCode() == 'A' && eventSequence[i].getDescriptor() == "start" )
			{

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
				" - OS: preparing process 1" << endl; 

			stateManager.setState(1);	//set PCB to ready

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
				" - OS: starting process 1" << endl;

			}

		else if ( eventSequence[i].getCode() == 'A' && eventSequence[i].getDescriptor() == "end" )
			{

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
				" - OS: removing process 1" << endl; 

			}


		//handle P code events 

		else if ( eventSequence[i].getCode() == 'P' )
			{

			stateManager.setState(2);	//set PCB to running

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
				" - Process 1: start processing action" << endl;

			usleep( 1000 * eventSequence[i].getCycles() * processorCycleTime); //wait for operation to complete

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
				" - Process 1: end processing action" << endl;

			}

		//handle I code events

		else if ( eventSequence[i].getCode() == 'I' && eventSequence[i].getDescriptor() == "hard drive" )
			{

			//wait until a hard drive resource is unlocked

			sem_wait(&hardDriveSemaphore);

			//got past lock- perform simulation

				currentHardDriveTemp = currentHardDrive;
				currentHardDrive = ( currentHardDrive + 1 ) % hardDriveQuantity;

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
						<< " - Process 1: start hard drive input on HDD " << currentHardDriveTemp << endl;

				msToRun = eventSequence[i].getCycles() * hardDriveCycleTime;

				pthread_create( &threads[0], NULL, runner, (void*)msToRun ); //create thread which will "run" this event

				stateManager.setState(3); 		//set PCB to waiting until thread complete

				pthread_join( threads[0], NULL ); 	//wait until thread complete

				stateManager.setState(1);		//set PCB to ready

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
						<< " - Process 1: end hard drive input" << endl;

			//done with a hard drive resource, unlock the semaphore

			sem_post(&hardDriveSemaphore);

			}

		else if ( eventSequence[i].getCode() == 'I' && eventSequence[i].getDescriptor() == "keyboard" )
			{

			//wait until keyboard resource is unlocked

			sem_wait(&keyboardSemaphore);

			//got past lock- perform simulation

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: start keyboard input" << endl;

				msToRun = eventSequence[i].getCycles() * keyboardCycleTime;

				pthread_create( &threads[0], NULL, runner, (void*)msToRun ); //create thread which will "run" this event

				stateManager.setState(3); 		//set PCB to waiting until thread complete

				pthread_join( threads[0], NULL ); 	//wait until thread complete

				stateManager.setState(1);		//set PCB to ready

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: end keyboard input" << endl;

			//done with keyboard resource, unlock the semaphore

			sem_post(&keyboardSemaphore);

			}

		else if ( eventSequence[i].getCode() == 'I' && eventSequence[i].getDescriptor() == "mouse" )
			{

			//wait until mouse resource is unlocked

			sem_wait(&mouseSemaphore);

			//got past lock- perform simulation

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: start mouse input" << endl;

				msToRun = eventSequence[i].getCycles() * mouseCycleTime;

				pthread_create( &threads[0], NULL, runner, (void*)msToRun ); //create thread which will "run" this event

				stateManager.setState(3); 		//set PCB to waiting until thread complete

				pthread_join( threads[0], NULL ); 	//wait until thread complete

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: end mouse input" << endl;

				stateManager.setState(1);		//set PCB to ready

			//done with mouse resource, unlock the semaphore

			sem_post(&mouseSemaphore);

			}

		//handle O code events

		else if ( eventSequence[i].getCode() == 'O' && eventSequence[i].getDescriptor() == "hard drive" )
			{

			//wait until a hard drive resource is unlocked

			sem_wait(&hardDriveSemaphore);

			//got past lock- perform simulation

				currentHardDriveTemp = currentHardDrive;
				currentHardDrive = ( currentHardDrive + 1 ) % hardDriveQuantity;

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0
					<< " - Process 1: start hard drive output on HDD " << currentHardDriveTemp << endl;

				msToRun = eventSequence[i].getCycles() * hardDriveCycleTime;

				pthread_create( &threads[0], NULL, runner, (void*)msToRun ); //create thread which will "run" this event

				stateManager.setState(3); 		//set PCB to waiting until thread complete

				pthread_join( threads[0], NULL ); 	//wait until thread complete

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: end hard drive output" << endl;

				stateManager.setState(1);		//set PCB to ready

			//done with a hard drive resource, unlock the semaphore

			sem_post(&hardDriveSemaphore);

			}

		else if ( eventSequence[i].getCode() == 'O' && eventSequence[i].getDescriptor() == "monitor" )
			{

			//wait until monitor resource is unlocked

			sem_wait(&monitorSemaphore);

			//got past lock- perform simulation

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: start monitor output" << endl;

				msToRun = eventSequence[i].getCycles() * monitorDisplayTime;

				pthread_create( &threads[0], NULL, runner, (void*)msToRun ); //create thread which will "run" this event

				stateManager.setState(3); 		//set PCB to waiting until thread complete

				pthread_join( threads[0], NULL ); 	//wait until thread complete

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: end monitor output" << endl;

				stateManager.setState(1);		//set PCB to ready

			//done with monitor resource, unlock the semaphore

			sem_post(&monitorSemaphore);

			}

		else if ( eventSequence[i].getCode() == 'O' && eventSequence[i].getDescriptor() == "printer" )
			{

			//wait until a printer resource is unlocked

			sem_wait(&printerSemaphore);

			//got past lock- perform simulation

				currentPrinterTemp = currentPrinter;
				currentPrinter = ( currentPrinter + 1 ) % printerQuantity;

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
					" - Process 1: start printer output on PRNTR " << currentPrinterTemp << endl;

				msToRun = eventSequence[i].getCycles() * printerCycleTime;

				pthread_create( &threads[0], NULL, runner, (void*)msToRun ); //create thread which will "run" this event

				stateManager.setState(3); 		//set PCB to waiting until thread complete

				pthread_join( threads[0], NULL ); 	//wait until thread complete

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: end printer output" << endl;

				stateManager.setState(1);		//set PCB to ready

			//done with a printer resource, unlock semaphore

			sem_post(&printerSemaphore);

			}
		

		//handle M code events

		else if ( eventSequence[i].getCode() == 'M' && eventSequence[i].getDescriptor() == "allocate" )
			{

			stateManager.setState(2);	//set PCB to running

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
				<< " - Process 1: allocating memory" << endl;

			currentBlockTemp = currentBlock;
			currentBlock = simMemory(currentBlock);

			usleep( 1000 * eventSequence[i].getCycles() * memoryCycleTime); //wait for operation to complete

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
				<< " - Process 1: memory allocated at 0x" << hex << setfill('0') << setw(8) << right << currentBlockTemp << dec << endl;

			}

		else if ( eventSequence[i].getCode() == 'M' && eventSequence[i].getDescriptor() == "block" )
			{

			stateManager.setState(2);	//set PCB to running

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
				<< " - Process 1: start memory blocking" << endl;

			usleep( 1000 * eventSequence[i].getCycles() * memoryCycleTime); //wait for operation to complete

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
				<< " - Process 1: end memory blocking" << endl;

			}

		}
duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
				" - Simulator program starting" << endl; 

			stateManager.setState(0); //initialize PCB with start state

			}

		else if ( eventSequence[i].getCode() == 'S' && eventSequence[i].getDescriptor() == "end" )
			{

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0  << 
				" - Simulator program ending" << endl; 

			stateManager.setState(4); //set PCB to exit state

			}

		//handle A code events

		else if ( eventSequence[i].getCode() == 'A' && eventSequence[i].getDescriptor() == "start" )
			{

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
				" - OS: preparing process 1" << endl; 

			stateManager.setState(1);	//set PCB to ready

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
				" - OS: starting process 1" << endl;

			}

		else if ( eventSequence[i].getCode() == 'A' && eventSequence[i].getDescriptor() == "end" )
			{

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
				" - OS: removing process 1" << endl; 

			}


		//handle P code events 

		else if ( eventSequence[i].getCode() == 'P' )
			{

			stateManager.setState(2);	//set PCB to running

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
				" - Process 1: start processing action" << endl;

			usleep( 1000 * eventSequence[i].getCycles() * processorCycleTime); //wait for operation to complete

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
				" - Process 1: end processing action" << endl;

			}

		//handle I code events

		else if ( eventSequence[i].getCode() == 'I' && eventSequence[i].getDescriptor() == "hard drive" )
			{

			//wait until a hard drive resource is unlocked

			sem_wait(&hardDriveSemaphore);

			//got past lock- perform simulation

				currentHardDriveTemp = currentHardDrive;
				currentHardDrive = ( currentHardDrive + 1 ) % hardDriveQuantity;

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
						<< " - Process 1: start hard drive input on HDD " << currentHardDriveTemp << endl;

				msToRun = eventSequence[i].getCycles() * hardDriveCycleTime;

				pthread_create( &threads[0], NULL, runner, (void*)msToRun ); //create thread which will "run" this event

				stateManager.setState(3); 		//set PCB to waiting until thread complete

				pthread_join( threads[0], NULL ); 	//wait until thread complete

				stateManager.setState(1);		//set PCB to ready

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
						<< " - Process 1: end hard drive input" << endl;

			//done with a hard drive resource, unlock the semaphore

			sem_post(&hardDriveSemaphore);

			}

		else if ( eventSequence[i].getCode() == 'I' && eventSequence[i].getDescriptor() == "keyboard" )
			{

			//wait until keyboard resource is unlocked

			sem_wait(&keyboardSemaphore);

			//got past lock- perform simulation

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: start keyboard input" << endl;

				msToRun = eventSequence[i].getCycles() * keyboardCycleTime;

				pthread_create( &threads[0], NULL, runner, (void*)msToRun ); //create thread which will "run" this event

				stateManager.setState(3); 		//set PCB to waiting until thread complete

				pthread_join( threads[0], NULL ); 	//wait until thread complete

				stateManager.setState(1);		//set PCB to ready

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: end keyboard input" << endl;

			//done with keyboard resource, unlock the semaphore

			sem_post(&keyboardSemaphore);

			}

		else if ( eventSequence[i].getCode() == 'I' && eventSequence[i].getDescriptor() == "mouse" )
			{

			//wait until mouse resource is unlocked

			sem_wait(&mouseSemaphore);

			//got past lock- perform simulation

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: start mouse input" << endl;

				msToRun = eventSequence[i].getCycles() * mouseCycleTime;

				pthread_create( &threads[0], NULL, runner, (void*)msToRun ); //create thread which will "run" this event

				stateManager.setState(3); 		//set PCB to waiting until thread complete

				pthread_join( threads[0], NULL ); 	//wait until thread complete

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: end mouse input" << endl;

				stateManager.setState(1);		//set PCB to ready

			//done with mouse resource, unlock the semaphore

			sem_post(&mouseSemaphore);

			}

		//handle O code events

		else if ( eventSequence[i].getCode() == 'O' && eventSequence[i].getDescriptor() == "hard drive" )
			{

			//wait until a hard drive resource is unlocked

			sem_wait(&hardDriveSemaphore);

			//got past lock- perform simulation

				currentHardDriveTemp = currentHardDrive;
				currentHardDrive = ( currentHardDrive + 1 ) % hardDriveQuantity;

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0
					<< " - Process 1: start hard drive output on HDD " << currentHardDriveTemp << endl;

				msToRun = eventSequence[i].getCycles() * hardDriveCycleTime;

				pthread_create( &threads[0], NULL, runner, (void*)msToRun ); //create thread which will "run" this event

				stateManager.setState(3); 		//set PCB to waiting until thread complete

				pthread_join( threads[0], NULL ); 	//wait until thread complete

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: end hard drive output" << endl;

				stateManager.setState(1);		//set PCB to ready

			//done with a hard drive resource, unlock the semaphore

			sem_post(&hardDriveSemaphore);

			}

		else if ( eventSequence[i].getCode() == 'O' && eventSequence[i].getDescriptor() == "monitor" )
			{

			//wait until monitor resource is unlocked

			sem_wait(&monitorSemaphore);

			//got past lock- perform simulation

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: start monitor output" << endl;

				msToRun = eventSequence[i].getCycles() * monitorDisplayTime;

				pthread_create( &threads[0], NULL, runner, (void*)msToRun ); //create thread which will "run" this event

				stateManager.setState(3); 		//set PCB to waiting until thread complete

				pthread_join( threads[0], NULL ); 	//wait until thread complete

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: end monitor output" << endl;

				stateManager.setState(1);		//set PCB to ready

			//done with monitor resource, unlock the semaphore

			sem_post(&monitorSemaphore);

			}

		else if ( eventSequence[i].getCode() == 'O' && eventSequence[i].getDescriptor() == "printer" )
			{

			//wait until a printer resource is unlocked

			sem_wait(&printerSemaphore);

			//got past lock- perform simulation

				currentPrinterTemp = currentPrinter;
				currentPrinter = ( currentPrinter + 1 ) % printerQuantity;

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 << 
					" - Process 1: start printer output on PRNTR " << currentPrinterTemp << endl;

				msToRun = eventSequence[i].getCycles() * printerCycleTime;

				pthread_create( &threads[0], NULL, runner, (void*)msToRun ); //create thread which will "run" this event

				stateManager.setState(3); 		//set PCB to waiting until thread complete

				pthread_join( threads[0], NULL ); 	//wait until thread complete

				end = std::chrono::high_resolution_clock::now();

				fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
					<< " - Process 1: end printer output" << endl;

				stateManager.setState(1);		//set PCB to ready

			//done with a printer resource, unlock semaphore

			sem_post(&printerSemaphore);

			}
		

		//handle M code events

		else if ( eventSequence[i].getCode() == 'M' && eventSequence[i].getDescriptor() == "allocate" )
			{

			stateManager.setState(2);	//set PCB to running

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
				<< " - Process 1: allocating memory" << endl;

			currentBlockTemp = currentBlock;
			currentBlock = simMemory(currentBlock);

			usleep( 1000 * eventSequence[i].getCycles() * memoryCycleTime); //wait for operation to complete

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
				<< " - Process 1: memory allocated at 0x" << hex << setfill('0') << setw(8) << right << currentBlockTemp << dec << endl;

			}

		else if ( eventSequence[i].getCode() == 'M' && eventSequence[i].getDescriptor() == "block" )
			{

			stateManager.setState(2);	//set PCB to running

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
				<< " - Process 1: start memory blocking" << endl;

			usleep( 1000 * eventSequence[i].getCycles() * memoryCycleTime); //wait for operation to complete

			end = std::chrono::high_resolution_clock::now();

			fout << fixed << (std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count()) / 1000000.0 
				<< " - Process 1: end memory blocking" << endl;

			}

		}

