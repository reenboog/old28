//
//  Quest.h
//  old28
//
//  Created by reenboog on 15.12.13.
//
//

#ifndef __old28__Quest__
#define __old28__Quest__

#include <string>
#include <vector>
#include <map>

using namespace std;

enum StatType {
    ST_Money,
    ST_Health,
    ST_Kindness,
    ST_Socials,
    ST_Gen,
    ST_Age
};

typedef map<StatType, int> StatPool;

struct StatGroup {
    StatGroup(const StatGroup &src) {
        stats = src.stats;
    }
    
    StatGroup() {
        this->addStat(ST_Money, 0);
        this->addStat(ST_Health, 0);
        this->addStat(ST_Kindness, 0);
        this->addStat(ST_Socials, 0);
        this->addStat(ST_Gen, 0);
        this->addStat(ST_Age, 5);
    }
    
    void addStat(StatType type, int value) {
        for(auto it = stats.begin(); it != stats.end(); ++it) {
            stats[type] = value;
        }
    }
    
    void apply(const StatGroup &src) {
        for(auto it = stats.begin(); it != stats.end(); ++it) {
            for(auto srcIt = src.stats.begin(); srcIt != src.stats.end(); ++srcIt) {
                if(it->first == srcIt->first) {
                    if(it->first != ST_Gen) {
                        it->second += srcIt->second;
                    } else {
                        it->second = srcIt->second;
                    }
                }
            }
        }
    }
    
    StatPool stats;
};


enum CompareType {
    CT_LessThan,
    CT_BiggerThan,
    CT_Equals
};

struct TransitionOption {
    int value;
    CompareType compareType;
    StatType statType;
    
    bool test(int valueToCompare) {
        switch(compareType) {
            case CT_LessThan:
                return valueToCompare < value;
            case CT_BiggerThan:
                return valueToCompare > value;
            case CT_Equals:
                return valueToCompare == value;
        }
        
        return false;
    }
};

typedef vector<TransitionOption> TransitionOptionPool;

struct QuestAnswerTransition {
    bool test(const StatGroup &statsToTest) {
        for(auto it = requiredOptions.begin(); it != requiredOptions.end(); ++it) {
            for(auto testIt = statsToTest.stats.begin(); testIt != statsToTest.stats.end(); ++testIt) {
                if(it->statType == testIt->first) {
                    if(!it->test(testIt->second)) {
                        return false;
                    }
                }
            }
        }
        
        return true;
    }
    
    string message;
    int key;
    StatGroup statsToApply;
    TransitionOptionPool requiredOptions;
};

typedef vector<QuestAnswerTransition> QuestAnswerTransitionPool;

struct QuestAnswer {
    const QuestAnswerTransition& getNextTransition(const StatGroup &currentStats) {
        for(int i = transitions.size() - 1; i >= 0; --i) {
            if(transitions[i].test(currentStats)) {
                return transitions[i];
            }
        }
        
        return transitions[0];
    }
    
    string caption;
    QuestAnswerTransitionPool transitions;
};

typedef vector<QuestAnswer> QuestAnswerPool;

struct Quest {
    int key;
    string question;
    QuestAnswerPool answers;
};

#endif /* defined(__old28__Quest__) */
