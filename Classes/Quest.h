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
#include <stdlib.h>

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

class StatGroup {
public:
    StatGroup(const StatGroup &src) {
        stats = src.stats;
    }
    
    void clear() {
        stats.clear();
    }
    
    StatGroup() {
        //this->addStat(ST_Money, 0);
        this->addStat(ST_Health, -10);
        //this->addStat(ST_Kindness, 0);
        //this->addStat(ST_Socials, 0);
        //this->addStat(ST_Gen, 0);
        this->addStat(ST_Age, 5);
    }
    
    void addStat(StatType type, int value) {
        stats[type] = value;
    }
    
    const StatPool& getStats() const {return this->stats;}
    
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
    
private:
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

class QuestAnswerTransition {
public:
    const string& getMessage() const {return this->message;}
    void setMessage(string message) {this->message = message;}
    
    int getKey() const {return this->key;}
    void setKey(int key) {this->key = key;}
    
    void addStatToApply(StatType type, int value) {
        this->statsToApply.addStat(type, value);
    }
    
    const StatGroup& getStatsToApply() const {
        return this->statsToApply;
    }
    
    void addRequiredOptions(CompareType compareType, StatType statType, int value) {
        this->requiredOptions.push_back({value, compareType, statType});
    }
    
    bool test(const StatGroup &statsToTest) {
        for(auto it = requiredOptions.begin(); it != requiredOptions.end(); ++it) {
            for(auto testIt = statsToTest.getStats().begin(); testIt != statsToTest.getStats().end(); ++testIt) {
                if(it->statType == testIt->first) {
                    if(!it->test(testIt->second)) {
                        return false;
                    }
                }
            }
        }
        
        return true;
    }
private:
    string message;
    int key;
    StatGroup statsToApply;
    TransitionOptionPool requiredOptions;
};

typedef vector<QuestAnswerTransition> QuestAnswerTransitionPool;

class QuestAnswer {
public:
    const string& getGaption() const {return this->caption;}
    void setCaption(string caption) {this->caption = caption;}
    
    void addTransition(const QuestAnswerTransition &t) {
        this->transitions.push_back(t);
    }
    
    const QuestAnswerTransition& getNextTransition(const StatGroup &currentStats) {
        for(int i = transitions.size() - 1; i >= 0; --i) {
            if(transitions[i].test(currentStats)) {
                return transitions[i];
            }
        }
        
        return transitions[0];
    }
private:
    string caption;
    QuestAnswerTransitionPool transitions;
};

typedef vector<QuestAnswer> QuestAnswerPool;

class QuestEntry {
public:
    typedef pair<int, const QuestAnswer&> QuestIndexAnswerPair;
    typedef vector<QuestIndexAnswerPair> QuestAnswerIndicesPool;
    
    int getKey() const {return this->key;}
    void setKey(int key) {this->key = key;}
    
    const string& getQuestion() const {return this->question;}
    void setQuestion(string question) {this->question = question;}
    
    void addAnswer(const QuestAnswer &a) {
        this->answers.push_back(a);
    }
    
    const QuestAnswerTransition& applyAnswer(int answerKey, const StatGroup &stats) {
        printf("QuestAnswerTransition::applyAnswer(%i)\n", answerKey);
        return answers[answerKey].getNextTransition(stats);
    }
    
    QuestAnswerIndicesPool get2RandomAnswers() const {
        QuestAnswerIndicesPool result;
        
        vector<int> answersIndices;
        answersIndices.resize(answers.size());
        
        c_unique fromZeroToNMinusOne;
        std::generate(answersIndices.begin(), answersIndices.end(), fromZeroToNMinusOne);
        
        int firstIndex = answersIndices[rand() % answersIndices.size()];
        answersIndices.erase(answersIndices.begin() + firstIndex);
        
        int secondIndex = answersIndices[rand() % answersIndices.size()];
        
        result.push_back({firstIndex, answers[firstIndex]});
        result.push_back({secondIndex, answers[secondIndex]});
        
        return result;
    }
private:
    struct c_unique {
        int current;
        c_unique() {current = 0;}
        int operator()() {return current++;}
    };
    
    int key;
    string question;
    QuestAnswerPool answers;
};

typedef vector<QuestEntry> QuestEntryPool;

class Quest {
public:
    Quest();
    
    void load(string file);
    const QuestAnswerTransition& applyAnswer(int answerKey, const StatGroup &stats);
    const QuestEntry& visitEntryByKey(int key);
    const QuestEntry& start();
    
//    const QuestEntry& getCurrentEntry() {
//        return entries[currentEntryKey];
//    }
private:
    QuestEntryPool entries;
    int currentEntryKey;
};

#endif /* defined(__old28__Quest__) */
