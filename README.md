# philosophers

The dining philosophers problem in C: one thread per philosopher for the
mandatory part, one **process** per philosopher for the bonus, with named
semaphores as the only thing they share.

> Part of the **42 school curriculum**. Built by **Arda Aycan**.

It is a learning project, not a benchmark: the interesting part is not raw
speed but how little machinery the solution needs to detect a death when the
philosophers cannot see each other.

## The problem

N philosophers sit around a table. Between every pair there is one fork, so
each philosopher needs both neighbours' forks to eat. They alternate between
eating, sleeping and thinking, and die if they go `time_to_die` milliseconds
without starting a meal. The program prints every state change with a
timestamp and stops when someone dies, or when everyone has eaten a given
number of times.

## What is implemented

| | Mandatory (`philo/`) | Bonus (`philo_bonus/`) |
| --- | --- | --- |
| Unit | one thread per philosopher | one process per philosopher |
| Shared state | shared memory in one process | named POSIX semaphores only |
| Forks | one mutex per fork | one counting semaphore |
| Printing | print mutex | print semaphore |
| End of simulation | shared `sim_flag` | death semaphore + one monitor thread per process |
| Required meals | supported | supported |
| One philosopher | handled (dies on time) | handled (dies on time) |

Both binaries validate their arguments, reject impossible values, and clean up
their mutexes, semaphores, threads and processes on both the normal and the
error path.

## How death is detected

A central "monitor" that watches every philosopher is the obvious design, and
it works for the mandatory part because all threads share memory. It is not
possible in the bonus part: separate processes cannot read each other's
`last_meal_time`, and the allowed functions leave no shared memory to put it
in.

So the check lives where the information already is: **inside each
philosopher**.

1. `smart_sleep()` wakes every 500 µs and compares the philosopher's own last
   meal with `time_to_die`.
2. The philosopher that would die takes the print lock, prints `died` once,
   and flips the shared flag.
3. In the bonus it also posts the death semaphore. Every process has a tiny
   monitor thread blocked on that semaphore; when it wakes it clears the local
   flag, so every loop unwinds and the parent's `waitpid()` returns.

The same idea is used for the meal target: a philosopher that finishes its
required meals announces the end the same way. The parent never inspects the
children, and no process needs to know another process's state.

Two smaller details that keep the simulation stable:

- **Staggered start.** Three IPC semaphores and an odd/even rule stop every
  philosopher from grabbing the same fork at time zero. Without it, the
  first millisecond is a burst of identical "has taken a fork" lines.
- **Odd numbers of philosophers** get a longer thinking pause, so two
  neighbours do not settle into a rhythm where one of them always loses the
  race for a fork.

The mandatory part uses the same local check with a `sim_flag` protected by a
mutex, so it does not need a monitor thread either.

## Build

```bash
make -C philo          # ./philo/philo
make -C philo_bonus    # ./philo_bonus/philo_bonus
```

Both Makefiles use `-Wall -Wextra -Werror` and no external libraries beyond
pthreads and the C standard library.

## Run

```
./philo[_bonus] number_of_philosophers time_to_die time_to_eat time_to_sleep [meals]
```

- `number_of_philosophers` — 1 or more
- `time_to_die` — milliseconds without eating before death
- `time_to_eat` / `time_to_sleep` — milliseconds
- `meals` — optional; stop after every philosopher has eaten this many times

```bash
./philo/philo 5 800 200 200
./philo/philo 5 800 200 200 7
./philo_bonus/philo_bonus 4 410 200 200
```

A single philosopher has only one fork, so it always dies on time — that is
the expected outcome, not a bug.

## Output

```
0 2 has taken a fork
0 2 has taken a fork
0 2 is eating
200 2 is sleeping
200 4 has taken a fork
...
401 3 died
```

`timestamp_in_ms philosopher_id action`. Lines are never interleaved: each
message is printed while holding the print lock.

## Project layout

| Path | Contents |
| --- | --- |
| `philo/` | mandatory part: threads, mutexes |
| `philo/routine.c` | philosopher loop, eating, death check |
| `philo/init_sim_*.c` | mutex and state setup |
| `philo_bonus/` | bonus part: processes, named semaphores |
| `philo_bonus/routine_pt_*.c` | philosopher loop, eating, monitor thread |
| `philo_bonus/init_sim_pt_*.c` | semaphore creation and fork loop |

## Things to try

```bash
# someone must die
./philo/philo 4 310 200 100

# nobody should die
./philo/philo 5 800 200 200

# stop after seven meals each
./philo_bonus/philo_bonus 5 800 200 200 7

# the lonely philosopher
./philo_bonus/philo_bonus 1 200 100 100
```

Timing is checked against the wall clock, so a heavily loaded machine can
report a death a few milliseconds late. That is a scheduler effect, not a
logic error.

## Author

**Arda Aycan** ([@EpicYamo](https://github.com/EpicYamo)).
