# Geant4 AbortRun / AbortEvent Behavior Reproducer

## Overview

This is a minimal Geant4 application based on the official beginner course example.

It has been modified to reproduce and study the behavior of:

- `G4RunManager::AbortRun()`
- `G4RunManager::AbortEvent()`

across different execution modes:

- Sequential
- MT
- Tasking

---

## Modifications Introduced

Two small changes were added to the baseline example:

### 1. Asynchronous abort trigger

A `std::thread` is launched in `main()`:

- waits for 5 seconds
- creates an empty file named: `abort_stepping`


This acts as an external trigger for aborting the simulation.

---

### 2. Abort condition in SteppingAction

In `SteppingAction`, the following logic is added:

```cpp
if (std::ifstream("abort_stepping").good())
{
    G4RunManager::GetRunManager()->AbortEvent();
    G4RunManager::GetRunManager()->AbortRun(true);
}
```

This causes any event detecting the file to request:

- immediate event abortion
- run termination

## Observed Behavior

1. Sequential mode

The first event detecting the file triggers `AbortEvent()` and `AbortRun(true)` and the run terminates immediately and gracefully

2. MT mode

Same expected behavior as in sequential mode.

3. Tasking

Behavior differs significantly. It seems that events are processed in chunks (tasks) of 10k events (100M events total)

Observed effects when the abort condition in SteppingAction is fulfilled:
- simulation continues processing some events
- the events that are aborted have an ID in steps of 10 000 (not consecutive IDs)
- `AbortRun()` is invoked many times

```cpp
...
G4WT2 > [ABORT] file detected | threadID=2 (worker) | runID=0 | eventID=99920000 | fAbortCounter=2494
G4WT2 > End of Event action 99920000
G4WT1 > Begin Event action 99930000
G4WT1 > [ABORT] file detected | threadID=1 (worker) | runID=0 | eventID=99930000 | fAbortCounter=2494
G4WT1 > End of Event action 99930000
G4WT3 > Begin Event action 99940000
G4WT3 > [ABORT] file detected | threadID=3 (worker) | runID=0 | eventID=99940000 | fAbortCounter=2495
G4WT3 > End of Event action 99940000
G4WT0 > Begin Event action 99950000
G4WT0 > [ABORT] file detected | threadID=0 (worker) | runID=0 | eventID=99950000 | fAbortCounter=2493
G4WT0 > End of Event action 99950000
G4WT2 > Begin Event action 99960000
G4WT2 > [ABORT] file detected | threadID=2 (worker) | runID=0 | eventID=99960000 | fAbortCounter=2495
G4WT2 > End of Event action 99960000
G4WT1 > Begin Event action 99970000
G4WT1 > [ABORT] file detected | threadID=1 (worker) | runID=0 | eventID=99970000 | fAbortCounter=2495
G4WT1 > End of Event action 99970000
G4WT3 > Begin Event action 99980000
G4WT3 > [ABORT] file detected | threadID=3 (worker) | runID=0 | eventID=99980000 | fAbortCounter=2496
G4WT3 > End of Event action 99980000
G4WT0 > Begin Event action 99990000
G4WT0 > [ABORT] file detected | threadID=0 (worker) | runID=0 | eventID=99990000 | fAbortCounter=2494
G4WT0 > End of Event action 99990000
G4WT2 > End run action
G4WT1 > End run action
G4WT3 > End run action
G4WT0 > End run action
```
## Interpretation

It seems that in Tasking mode, execution is structured in two levels

- **task level**, work is divided into chunks and scheduled in advance
- **event loop** level, each worker processes events within its assigned chunk

The method `AbortRun()` appears to act only at the event loop level within a chunk/task, but not at the global scheduling level.

As a consequence, already scheduled tasks continue execution even after a run abort is requested.

## Expected behavior

According to the Geant4 documentation in the file `G4RunManager.hh` for `AbortRun` method, *AbortRun() safely aborts the current event loop [...] The application state will be changed to 'Idle'.*

Expected behavior:

- Immediate termination of the run
- No further event processing after abort run request

## Actual behavior for Tasking Run Manager

- Multiple abort calls are required
- Run continues until all scheduled tasks are drained
- Behavior depends on: number of threads, chunk size, total number of events
- This introduces backend-dependent behavior. This may be relevant for experiments such as ATLAS (see User Requirement 134)
