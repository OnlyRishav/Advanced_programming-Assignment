from __future__ import annotations

import math
import time
from collections import defaultdict
from functools import reduce
import heapq

SAMPLE_LOGS: list[dict] = [
    {"user": "S101", "action": "YouTube",   "duration": 45.0},
    {"user": "S102", "action": "Instagram", "duration": 30.0},
    {"user": "S101", "action": "Zoom",      "duration": 60.0},
    {"user": "S103", "action": "YouTube",   "duration": 20.0},
    {"user": "S102", "action": "Zoom",      "duration": 50.0},
    {"user": "S104", "action": "Netflix",   "duration": 90.0},
    {"user": "S101", "action": "Instagram", "duration": 25.0},
    {"user": "S103", "action": "Zoom",      "duration": 40.0},
    {"user": "S104", "action": "YouTube",   "duration": 35.0},
    {"user": "S105", "action": "Discord",   "duration": 55.0},
    {"user": "S102", "action": "Netflix",   "duration": 70.0},
    {"user": "S105", "action": "YouTube",   "duration": 80.0},
    {"user": "S103", "action": "Discord",   "duration": 15.0},
    {"user": "S104", "action": "Zoom",      "duration": 45.0},
    {"user": "S101", "action": "Discord",   "duration": 10.0},
]


def total_time_per_user(logs: list[dict]) -> dict[str, float]:
    def _acc(acc: defaultdict, entry: dict) -> defaultdict:
        acc[entry["user"]] += entry["duration"]
        return acc
    return dict(reduce(_acc, logs, defaultdict(float)))


def most_active_users(logs: list[dict], k: int) -> list[str]:
    totals = total_time_per_user(logs)
    return [u for u, _ in heapq.nlargest(k, totals.items(), key=lambda x: x[1])]


def unique_actions(logs: list[dict]) -> set[str]:
    return {entry["action"] for entry in logs}


def compute_time_complexity(logs: list[dict], k: int) -> str:
    n = len(logs)
    totals = total_time_per_user(logs)
    u = len(totals)
    a = len(unique_actions(logs))

    reduce_ops   = n
    nlargest_ops = u * math.log2(u) if u > 1 else 1
    topk_ops     = int(reduce_ops + nlargest_ops)

    print(f"  n (log entries)     = {n}")
    print(f"  u (unique users)    = {u}")
    print(f"  a (unique actions)  = {a}")
    print(f"  reduce step ops     = n         = {reduce_ops}")
    print(f"  nlargest step ops   = u*log2(u) = {u} * log2({u}) = {nlargest_ops:.2f}")
    print(f"  total ops (top-k)   = n + u*log2(u) = {topk_ops}")

    return f"O(n + u*log(u))  =>  {topk_ops} ops  [n={n}, u={u}]"


def compute_space_complexity(logs: list[dict]) -> str:
    totals  = total_time_per_user(logs)
    actions = unique_actions(logs)

    u = len(totals)
    a = len(actions)

    print(f"  u (unique users)    = {u}  =>  dict of size u")
    print(f"  a (unique actions)  = {a}  =>  set of size a")
    print(f"  total space units   = u + a = {u} + {a} = {u + a}")

    return f"O(u + a)  =>  {u + a} units  [u={u}, a={a}]"


if __name__ == "__main__":
    print("Total Time Per User:")
    print(total_time_per_user(SAMPLE_LOGS))

    print("\nTop 3 Most Active Users:")
    print(most_active_users(SAMPLE_LOGS, 3))

    print("\nUnique Actions:")
    print(unique_actions(SAMPLE_LOGS))

    print("\n===== COMPLEXITY ANALYSIS =====")

    print("\n-- Time Complexity (Top K Users) --")
    time_result = compute_time_complexity(SAMPLE_LOGS, k=3)
    print(f"  => {time_result}")

    print("\n-- Space Complexity --")
    space_result = compute_space_complexity(SAMPLE_LOGS)
    print(f"  => {space_result}")