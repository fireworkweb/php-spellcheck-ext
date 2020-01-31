#include <libvoikko/voikko.h>
#include <vector>
#include <iostream>
#include <phpcpp.h>

class VoikkoExt : public Php::Base
{
    private:
        VoikkoHandle * _handle = NULL;

    public:
        VoikkoExt() = default;
        virtual ~VoikkoExt() = default;

        void __construct(Php::Parameters &params);
        void __destruct();

        Php::Value check(Php::Parameters &params);
        Php::Value suggest(Php::Parameters &params);

        static Php::Class<VoikkoExt> getPhpClass();
};
